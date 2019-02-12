

#include "fft_algo.h"
#include <time.h>


#define ARR_SIZE 10000
int arrVal[ARR_SIZE];
int test_fft(int arr[],int start,int end);

int main()
{
srand(time(NULL));
for(int i = 0; i<ARR_SIZE; i++)
    {   
        arrVal[i] = rand();



    }

     if(quick_sort(arrVal,0,ARR_SIZE-1))
    {
        printf("Array Sorted");
    }
   


    if(!test_fft(arrVal,0,ARR_SIZE-1))
    {
        printf("ARRAY FAILED TEST PROCEDURE");
    }

}
int test_fft(int arr[],int start,int end)
{

    for(int i = 0; i < end;i++)
    {
        if(arr[i]>arr[i+1])return 0;
    }


    return 1;

}



