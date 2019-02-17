
#include "fft_algo.h"

#include <time.h>

//THIS ALGORITHM IS ONLY WRITTEN FOR POWERS OF 2


/**
 * @brief Tests the FFT generated
 * 
 * @param arr 
 * @param start 
 * @param end 
 * @return int 
 */
int test_fft(float arr[],int start,int end);

#if 1
float arrVal[ARR_SIZE]={0,
0.154508497187474,
0.293892626146237,
0.404508497187474,
0.475528258147577,
0.500000000000000,
0.475528258147577,
0.404508497187474} ;
#endif

float complex bins[ARR_SIZE];


int main()
{

        if(fft_algorithm(arrVal,bins,0,ARR_SIZE,ARR_SIZE))
        {
            printf("Array Sorted\n");
        }   
    
   
   
   float bins_mag[ARR_SIZE];
   for(int i = 0; i < ARR_SIZE/2;i++)
   {
       bins_mag[i] = cabs(bins[i]);
        printf("Bin %d Mag = %lf\n",i,bins_mag[i]);
   }
    // test_fft(bins_mag ,0,ARR_SIZE) ? printf("FFT ALGO PASSED") : printf("FFT FAILED");
   return 0;
}



/*
int test_fft(float arr[],int start,int end)
{
    for(int i = 0; i < end;i++)
    {
        if(arr[i]!=arr_test_array[i])return 0;
    }

    return 1;

}
*/


