/***************************************************************************
 * 
 * Homework for chapter 4 -- Adaptive filter using LMS & RLS
 *
 * Here is the realization of adapt_filtering function.
 * 
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "adapt_filt.h"

const double err_min = 1e-6;
const double mu = 0.2;
const double delta = 0.001;
const double lambda = 0.8;
const int filter_length = 128;
double* x = new double[filter_length]();
double* w = new double[filter_length]();
double* k = new double[filter_length]();
double* P = new double[filter_length * filter_length]();

/**
 * @brief time-domain adaptive filter algorithm
 *
 * @param input          input audio sample of time index(n)
 * @param filter_length  adaptive filter length, 128 by default
 * @param err            error output of time index(n)
 * @return 
 *     @retval 0         successfully
 */
int adapt_filtering(short input, short* err) {
    // update inputdata buffer. Each sample is normalized to [-1,1)
    for(size_t i = filter_length - 1; i > 0; i--) {
        x[i] = x[i - 1];
    }
    x[0] = double(input / 32768.0);

    // finish adaptive filtering algorithm here, using LMS and RLS, respectively
    // 1. calculate filter output, as well as necessary parameters
    double y = 0.0;
    for (size_t i = 0; i < filter_length; i++) {
        y += w[i] * x[i];
    }

    // expect output signal equals to input signal
    double error = x[0] - y;
    // 2. update filter: adapt_filter, for future iterations
    for (size_t i = 0; i < filter_length; i++) {
        w[i] += 2 * mu * x[i] * error;
    }
    // end adaptive filtering algorithm

    // output error
    err[0] = short(error * 32768.0);

    return 0;
}

/**
 * @brief time-domain adaptive recursive filter algorithm
 *
 * @param input          input audio sample of time index(n)
 * @param filter_length  adaptive filter length, 128 by default
 * @param err            error output of time index(n)
 * @return 
 *     @retval 0         successfully
 */
int adapt_recursive_filtering(short input, short* err) {
    // update inputdata buffer. Each sample is normalized to [-1,1)
    for(size_t i = filter_length - 1; i > 0; i--) {
        x[i] = x[i - 1];
    }
    x[0] = double(input / 32768.0);

    // finish adaptive filtering algorithm here, using LMS and RLS, respectively
    // 1. calculate filter output, as well as necessary parameters
    double y = 0.0;
    for (size_t i = 0; i < filter_length; i++) {
        y += w[i] * x[i];
    }

    // expect output signal equals to input signal
    double error = x[0] - y;
    if (fabs(error) > err_min) {
        // 2. update filter: adapt_filter, for future iterations
        double* Px = new double[filter_length]();
        double* xP = new double[filter_length]();
        double xPx = 0;
        for (size_t i = 0; i < filter_length; i++) {
            for (size_t j = 0; j < filter_length; j++) {
                Px[i] += P[i * filter_length + j] * x[j];
                xP[i] += x[j] * P[j * filter_length + i];
            }
            xPx += x[i] * Px[i];
        }

        // printf("%lf ", xPx);
        double* kxP = new double[filter_length * filter_length]();
        for (size_t i = 0; i < filter_length; i++) {
            k[i] = Px[i] / (lambda + xPx);
            for (size_t j = 0; j < filter_length; j++) {
                kxP[i * filter_length + j] += k[i] * xP[j];
            }
        }

        for (size_t i = 0; i < filter_length; i++) {
            for (size_t j = 0; j < filter_length; j++) {
                P[i * filter_length + j] -= kxP[i * filter_length + j];
                P[i * filter_length + j] /= lambda;
            }
        }

        for (size_t i = 0; i < filter_length; i++) {
            w[i] += k[i] * error;
        }
        // end adaptive filtering algorithm
    }

    // output error
    err[0] = short(error * 32768.0);

    return 0;
}
