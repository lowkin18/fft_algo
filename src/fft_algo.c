

//only RADIX 2 sizing capable need to make modifications if using variable size sample
// trying to implement the algorithm as inplace and bubble up amounts
#include "fft_algo.h"


complex float bincheck[ARR_SIZE];

/**
 * @brief function that will perform the FFT with DCT based the simplest Cooley & Tukey method
 * 
 * 
 * @param arr 
 * @param float 
 * @param index 
 * @param current_size 
 * @param total_size 
 * @return int 
 */
int fft_algorithm(float * arr,complex float *bins, int index,int current_size, int total_size)
{
    if(current_size == 1) return 1; //base case
    int next_size = current_size/2;
    int ptr_jump = total_size/current_size;
    //CREATE TWO NEW BINS TO PASS TO THE NEXT LAYER DOWN THESE BINS WILL BUBBLE UP
    complex float * even_bin = (complex float * )malloc(next_size*sizeof(complex float));
    complex float * odd_bin = (complex float * )malloc(next_size*sizeof(complex float));
    fft_algorithm(arr,even_bin,index,next_size,total_size); //CALL FFT AGAIN ON N/2
    fft_algorithm(arr,odd_bin,index+ptr_jump,next_size,total_size); //CALL FFT AGAIN ON N/2

    //BASE CASE WHERE N = 2 COMBINE TO CREATE 2 SAMPLE DFT
    if(current_size==2) //BASE CASE where Wn is easy
    {
        bins[0] = arr[index] + arr[index+ptr_jump];
        bins[1] = arr[index] - arr[index+ptr_jump];
        bincheck[0] = bins[0];
        bincheck[1] = bins[1];
    }
    //WHEN DFT LENGTH IS GREATER THAN 2 - THIS MERGES THE EVEN AND ODD BACK TOGETHER AND FORMS NEXT LEVEL BINS
    else
    {      
    int ptr_jump = total_size/current_size; //DETERMINES THE POWER OF Wn TERM
    for(int i = 0; i < current_size/2; i++)   //LOOPS THROUGH ODD AND EVEN MERGING THEM
        {
            if(i==0){
               bins[i] = even_bin[i] + odd_bin[i]; // FIRST BIN FROM ODD AND EVEN TWIDDLE ALWAYS 1
               bins[i+current_size/2] = even_bin[i] - odd_bin[i];
               bincheck[i] = bins[i];
               bincheck[i+current_size/2] = bins[i+current_size/2];
            } 
            else
            {
                float twid_real = cos((E_PI*2*i*ptr_jump)/total_size); //REAL TWIDDLE FACTOR
                float twid_imag = sin((E_PI*2*i*ptr_jump)/total_size); //IMAG TWIDDLE FACTOR
                complex float twiddle_factor = twid_real + I*twid_imag; //COMBINE TO CREATE COMPLEX NUMBER
                bins[i] = even_bin[i] + twiddle_factor*odd_bin[i];
                bins[i+current_size/2] = even_bin[i] - twiddle_factor*odd_bin[i]; //OFFSET TO ZERO SO 0 REFERENCED FOR FIRST ODD
                bincheck[i] = bins[i];
                bincheck[i+current_size/2] = bins[i+current_size/2];
            }
                    
        }
    }
    free(even_bin); //FREE THE DYNAMIC ARRAYS
    free(odd_bin); //FREE THE DYNAMIC ARRAYS
    return 1; //RETURN 1 ON CONDITION PASSED ::: NO ERROR CHECKING YET
}