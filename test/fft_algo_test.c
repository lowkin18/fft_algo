
#include "fft_algo.h"

#include <time.h>

//THIS ALGORITHM IS ONLY WRITTEN FOR POWERS OF 2



double arrVal[ARR_SIZE]={0,1,2,3,4,5,6,7};
double complex bins[ARR_SIZE];






int main()
{
    /*
    srand(time(NULL));
    for(int i = 0; i<ARR_SIZE; i++)
    {   
    arrVal[i] = rand();



    }
    */
    FFT_order_array(arrVal,ARR_SIZE);


     if(fft_algorithm(arrVal,bins,0,ARR_SIZE-1,ARR_SIZE))
    {
        printf("Array Sorted\n");
    }
   
   
   double bins_mag[ARR_SIZE];
   for(int i = 0; i < ARR_SIZE;i++)
   {
       bins_mag[i] = cabs(bins[i]);
        printf("Bin %d Mag = %lf\n",i,bins_mag[i]);
   }
   test_fft(bins_mag ,0,ARR_SIZE) ? printf("FFT ALGO PASSED") : printf("FFT FAILED");
   return 0;
}
int test_fft(double arr[],int start,int end)
{
    double arr_test_array[ARR_SIZE] = {28.000, 10.453, 5.657 ,4.330 ,4.000 ,4.330 ,5.657 ,10.453};
    for(int i = 0; i < end;i++)
    {
        if(arr[i]!=arr_test_array[i])return 0;
    }

    return 1;

}



