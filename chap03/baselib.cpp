/***************************************************************************
  * 
  * Homework for chapter 3 -- "overlap-save method"
  *
  * Here is the realization of FFT function.
  * The input/output data are stored in fftdata. FFT length should also be 
  * assigned.
  * 
  **************************************************************************/

#include <math.h>
#include <stddef.h>
#include "typedefs.h"
#include "baselib.h"

COMPLEX* dot(COMPLEX* x, COMPLEX* w, int len) {
    COMPLEX* y = new COMPLEX[len]();
    for (size_t i = 0; i < len; i++) {
        y[i] = x[i] * w[i];
    }
    
    return y;
}

void conjugate(COMPLEX* x, int len) {
    for (size_t i = 0; i < len; i++) {
        x[i].image *= -1;
    }
}

void scale(COMPLEX* x, int len) {
    for (size_t i = 0; i < len; i++) {
        x[i].real /= len;
        x[i].image /= len;
    }
}

void Rader(COMPLEX* x, int len) {
    int j = len >> 1;
    for (int i = 1; i < len - 1; i++) {
        if (i < j) {
            std::swap(x[i], x[j]);
        }

        int k = len >> 1;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) {
            j += k;
        }
    }
}

void fft(COMPLEX* fftdata, int fftorder) {
    int len = 1 << fftorder;
    Rader(fftdata, len);

    for (int l = 2; l <= len; l <<= 1) {
        COMPLEX wn((float) cos(2 * PI / l), (float) sin(-2 * PI / l));
        for (int i = 0; i < len; i += l) {
            COMPLEX w(1, 0); // rotate factor
            for (int j = i; j < i + (l >> 1); j++) {
                COMPLEX t = w * fftdata[j + (l >> 1)];
                fftdata[j + (l >> 1)] = fftdata[j] - t;
                fftdata[j] += t;
                w = w * wn;
            }
        }
    }
}

void ifft(COMPLEX* ifftdata, int fftorder) {
    int len = 1 << fftorder;
    conjugate(ifftdata, len);
    fft(ifftdata, fftorder);
    scale(ifftdata, len);
    conjugate(ifftdata, len);
}
