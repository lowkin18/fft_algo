


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

#define ARR_SIZE 8

#ifndef FFT_ALGO_HEADER
#define FFT_ALGO_HEADER

#endif






//type def for complex numbers for the twiddles



/**
 * @brief Orders the array into correct byte order requires a lookup table
 *
 * 
 * @param arr 
 * @param size 
 */
void FFT_order_array(float arr[],int size);




/**
 * @brief Function that takes in an array of samples and gives back the FFT bins
 *        Total_size must be radix 2 otherwise function wont work
 * 
 * @param arr 
 * @param complex float - This is the bins
 * @param index 
 * @param index_right 
 * @param total_size 
 * @return int 
 */
int fft_algorithm(float * arr,complex float *bins,int left, int right, int total_size);



//NEXT STEP IS WRITE THE IFFT
int ifft_algorithm(float * arr,complex float *bins,int left, int right, int total_size);