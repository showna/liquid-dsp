#ifndef __FIR_FILTER_AUTOTEST_H__
#define __FIR_FILTER_AUTOTEST_H__

#include "../src/filter.h"

void autotest_create_external_coeff_01() {

    // Initialize pre-determined coefficient array
    float h[8] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f };

    // Create filter
    fir_filter f = fir_filter_create(h, 8);

    // Assert arrays are the same length
    CONTEND_EQUALITY( fir_filter_get_length(f), 8 );

    fir_filter_destroy(f);
}

void autotest_impulse_response() {

    // Initialize variables
    float h[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    float x[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    x[9] = 1.0f;
    float y;       // output

    // Load filter coefficients externally
    fir_filter f = fir_filter_create(h, 10);

    unsigned int i;
    // Resulting output should be equal to filter coefficients
    for (i=0; i<10; i++) {
        y = fir_filter_execute(f, &x[i]);
        CONTEND_EQUALITY( y, h[i]);
    }

    // Impulse response should be finite
    for (i=10; i<20; i++) {
        y = fir_filter_execute(f, &x[i]);
        CONTEND_DELTA( 0.0f, y, 0.001 );
    }

    fir_filter_destroy(f);
}

void autotest_noise_01()
{
    // Initialize variables
    float h[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

    // noise signal
    float x[41] = {         // length: 32+9
        0,0,0,0,0,0,0,0,0,  // nine zeros (filter delay)
        0.704280,     0.093701,    -0.812560,    -1.062200, 
       -0.163140,    -0.358630,     1.343000,    -0.929300, 
        0.912920,    -0.286200,    -2.225000,     0.500690, 
        1.113100,     0.460800,     0.138420,     0.574660, 
       -1.561200,    -0.343980,    -0.337980,    -0.090664, 
        0.410950,     0.215070,     0.497200,    -0.927120, 
        1.653200,    -0.156370,    -1.092900,     0.443410, 
       -0.377020,    -0.646710,    -0.190430,    -0.697070
    };
    
    // test output
    float test[32] = {
        0.070428,     0.150230,     0.148770,     0.041088, 
       -0.082907,    -0.242760,    -0.268320,    -0.386800, 
       -0.414000,    -0.469810,    -1.522800,    -1.924600, 
       -1.227500,    -0.128440,     0.101680,     0.620620, 
       -0.852520,     0.005200,    -1.104400,    -0.995290, 
        1.316200,     0.873450,    -0.243340,    -0.846600, 
       -0.976010,    -1.614800,    -0.070856,     0.334600, 
        0.730150,     0.822780,     0.353650,    -0.010807
    };

    float y;    // ouput


    // Load filter coefficients externally
    fir_filter f = fir_filter_create(h, 10);

    unsigned int i;
    // 
    for (i=0; i<32; i++) {
        y = fir_filter_execute(f, &x[i]);
        CONTEND_DELTA( test[i], y, 0.001 );
    }

    fir_filter_destroy(f);
}


#endif // __FIR_FILTER_AUTOTEST_H__

