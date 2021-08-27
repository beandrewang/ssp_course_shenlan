/***************************************************************************
 * 
 * Homework for chapter 4 -- Adaptive filter using LMS & RLS
 *
 * Here is the declaration of adapt_filtering function.
 * 
 **************************************************************************/

#ifndef _ADAPT_FILT_H_
#define _ADAPT_FILT_H_

extern const double mu;
extern const double delta;
extern const double lambda;
extern const int filter_length;
extern double* x;
extern double* w;
extern double* k;
extern double* P;

int adapt_filtering(short input, short* err);

int adapt_recursive_filtering(short input, short* err);

#endif
