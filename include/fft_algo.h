


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

#define ARR_SIZE 8

#ifndef FFT_ALGO_HEADER
#define FFT_ALGO_HEADER

#endif


#define SWAP(a,b) (a)^=(b)^=(a)^=(b)




//type def for complex numbers for the twiddles




void FFT_order_array(double arr[],int size);

int test_fft(double arr[],int start,int end);


/**
 * @brief Function assumes the array has been ordered correctly with reverse bit order
 * 
 * @param arr 
 * @param complex 
 * @param index 
 * @param index_right 
 * @param total_size 
 * @return int 
 */
int fft_algorithm(double * arr,double complex *bins,int left, int right, int total_size);
