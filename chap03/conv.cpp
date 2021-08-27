/***************************************************************************
 * 
 * Homework for chapter 3 -- "overlap-save method"
 *
 * Here is the realization of add rir function.
 * You have to finish "conv" function by yourself. It is called in main 
 * function. Also, you may want to use FFT, which is ready for you too.
 *
 * NOTICE: There is no IFFT function. So you have to realize IFFT using FFT.
 * Take some time to think about how to do this please.
 * 
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "conv.h"
#include "baselib.h"
#include "typedefs.h"

/**
 * @brief add rir using overlap-save method.
 *
 * @param inputdata         input clean audio data buffer
 * @param inputdata_length  length of inputdata(samples)
 * @param rir               room impulse response buffer
 * @param rir_length        length of rir, 4096 by default
 * @param outputdata        processed data, same length as inputdata
 * @return 
 *     @retval 0            successfully
 */
int conv(short* inputdata, long inputdata_length, double* rir, long rir_length, short* outputdata) {
    // finish overlap-save method here
    int N = rir_length;
    int N1 = rir_length << 1;
    int fftorder = (int) log2(N1);

    // Zero padding
    COMPLEX* w = new COMPLEX[N1]();
    for (size_t i = 0; i < N; i++) {
        w[i].real = rir[i];
    }
    fft(w, fftorder);

    int pos = 0;
    COMPLEX* x = new COMPLEX[N1]();
    COMPLEX* old = new COMPLEX[N]();
    while (pos < inputdata_length) {
        for (size_t i = 0; i < N; i++) {
            float real = (pos + i < inputdata_length) ? inputdata[pos + i] : 0;
            x[i + N] = COMPLEX(real, 0);
            x[i] = old[i];
            old[i] = x[i + N];
        }
        fft(x, fftorder);

        COMPLEX* y = dot(x, w, N1);
        ifft(y, fftorder);
        for (size_t i = N; i < N1 && pos < inputdata_length; i++) {
            outputdata[pos++] = y[i].real;
        }
    }

    delete [] w;
    delete [] x;
    delete [] old;
    return 0;
}

int linear_conv(short* inputdata, long inputdata_length, double* rir, long rir_length, short* outputdata) {
    int N = inputdata_length;

    float* y = new float[N]();
    for (size_t i = 0; i < N; i++) {
        size_t jmin = (i >= rir_length - 1) ? i - (rir_length - 1) : 0;
        size_t jmax = (i < inputdata_length - 1) ? i : inputdata_length - 1;
        for (size_t j = jmin; j <= jmax; j++) {
            y[i] += inputdata[j] * rir[i - j];
        }
    }

    for (size_t i = 0; i < inputdata_length; i++) {
        outputdata[i] = y[i];
    }

    delete [] y;
    return 0;
}

int circular_conv(short* inputdata, long inputdata_length, double* rir, long rir_length, short* outputdata) {
    int N = inputdata_length << 1;
    int fftorder = (int) log2(N);

    COMPLEX* x = new COMPLEX[N]();
    COMPLEX* w = new COMPLEX[N]();
    for (size_t i = 0; i < N; i++) {
        float real = (i < rir_length) ? rir[i] : 0;
        w[i] = COMPLEX(real, 0);
        real = (i < inputdata_length) ? inputdata[i] : 0;
        x[i] = COMPLEX(real, 0);
    }
    fft(w, fftorder);
    fft(x, fftorder);

    COMPLEX* y = dot(x, w, N);
    ifft(y, fftorder);
    for (size_t i = 0; i < inputdata_length; i++) {
        outputdata[i] = y[i].real;
    }

    delete [] w;
    delete [] x;
    delete [] y;
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
