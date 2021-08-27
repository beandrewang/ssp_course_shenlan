/***************************************************************************
 * 
 * Homework for chapter 3 -- "overlap-save method"
 *
 * Here is the declaration of FFT function.
 * The input/output data are stored in fftdata. FFT length should also be 
 * assigned.
 * 
 **************************************************************************/

#ifndef  __BASELIB_H_
#define  __BASELIB_H_

#include "typedefs.h"

/** dot */
COMPLEX* dot(COMPLEX* x, COMPLEX* w, int len);

/** conjugate */
void conjugate(COMPLEX* x, int len);

/** scale */
void scale(COMPLEX* x, int len);

/** Rader algorithm */
void Rader(COMPLEX* x, int len);

/** @brief FFT */
void fft(COMPLEX* fftdata, int fftorder);

/** @brief IFFT */
void ifft(COMPLEX* ifftdata, int fftorder);

#endif  //__BASELIB_H_
