

//only RADIX 2 sizing capable need to make modifications if using variable size sample
// trying to implement the algorithm as inplace and bubble up amounts

#include "fft_algo.h"
/**
 * @brief 
 * 
 * @param arr 
 * @param left_index location of start of odd value
 * @param right_index 
 * @param total_size 
 * @return int 
 */

double bin_check[ARR_SIZE] = {0,0,0,0,0,0,0,0};

int bit_r_8[8] = {0 ,4 ,2 ,6 ,1 ,5 ,3 ,7};
int bit_r_16[16] = {0 ,8 ,4 ,12 ,2 ,10 ,6 ,14 ,1 ,9 ,5 ,13 ,3 ,11 ,7 ,15};
int bit_r_32[32] = {0 ,16 ,8 ,24 ,4 ,20 ,12 ,28 ,2 ,18 ,10 ,26 ,6 ,22 ,14 ,30 ,1 ,17 ,9 ,25 ,5 ,21 ,13 ,29 ,3 ,19 ,11 ,27 ,7 ,23 ,15 ,31};
int bit_r_64[64] = {0 ,16 ,8 ,24 ,4 ,20 ,12 ,28 ,2 ,18 ,10 ,26 ,6 ,22 ,14 ,30 ,1 ,17 ,9 ,25 ,5 ,21 ,13 ,29 ,3 ,19 ,11 ,27 ,7 ,23 ,15 ,31 ,
                1 ,33 ,17 ,49 ,9 ,41 ,25 ,57 ,5 ,37 ,21 ,53 ,13 ,45 ,29 ,61 ,3 ,35 ,19 ,51 ,11 ,43 ,27 ,59 ,7 ,39 ,23 ,55 ,15 ,47 ,31 ,63};

int bit_r_128[128] = {0 ,16 ,8 ,24 ,4 ,20 ,12 ,28 ,2 ,18 ,10 ,26 ,6 ,22 ,14 ,30 ,1 ,17 ,9 ,25 ,5 ,21 ,13 ,29 ,3 ,19 ,11 ,27 ,7 ,23 ,15 ,31 ,1 ,33 ,
17 ,49 ,9 ,41 ,25 ,57 ,5 ,37 ,21 ,53 ,13 ,45 ,29 ,61 ,3 ,35 ,19 ,51 ,11 ,43 ,27 ,59 ,7 ,39 ,23 ,55 ,15 ,47 ,31 ,63 ,1 ,65 ,33 ,97 ,17 ,81 ,49 ,
113 ,9 ,73 ,41 ,105 ,25 ,89 ,57 ,121 ,5 ,69 ,37 ,101 ,21 ,85 ,53 ,117 ,13 ,77 ,45 ,109 ,29 ,93 ,61 ,125 ,3 ,67 ,35 ,99 ,19 ,83 ,51 ,115 ,11 ,75 ,
43 ,107 ,27 ,91 ,59 ,123 ,7 ,71 ,39 ,103 ,23 ,87 ,55 ,119 ,15 ,79 ,47 ,111 ,31 ,95 ,63 ,127 ,};


int bit_r_256[256] = {0 ,8 ,4 ,12 ,2 ,10 ,6 ,14 ,1 ,9 ,5 ,13 ,3 ,11 ,7 ,15};
int bit_r_512[512] = {0 ,8 ,4 ,12 ,2 ,10 ,6 ,14 ,1 ,9 ,5 ,13 ,3 ,11 ,7 ,15};
int bit_r_1024[1024] = {0 ,8 ,4 ,12 ,2 ,10 ,6 ,14 ,1 ,9 ,5 ,13 ,3 ,11 ,7 ,15};


/**
 * @brief 
 * 
 * @param arr 
 * @param size 
 */
void FFT_order_array(double arr[],int size)
{
    double complex temp_array[64];
    for(int i = 0; i < size ;i++)
    {
        temp_array[i] = arr[bit_r_8[i]];
    }
      for(int i = 0; i < size ;i++)
    {
        arr[i] = temp_array[i];
    }
}



/**
 * @brief 
 * 
 * @param arr 
 * @param complex 
 * @param left 
 * @param right 
 * @param total_size 
 * @return int 
 */
/*
int fft_algorithm(double * arr,double complex *bins, int left,int right, int total_size)
{

    if(left>=right) return 1; //base case

    int middle= (right+left)/2;
    int current_size = right-left+1;

    fft_algorithm(arr,bins,left,middle,total_size);
    fft_algorithm(arr,bins,middle+1,right,total_size);


    if(current_size==2) //BASE CASE where Wn is easy
    {
        bins[left] = arr[left] + arr[right];
        bins[right] = arr[left] - arr[right];
        bin_check[left] = arr[left] + arr[right];
        bin_check[right] = arr[left] - arr[right];
    }
    else
    {
    
    int ptr_jump = total_size/current_size; // NEEDED FOR Wn
    int iMult = 1; //Multiplier to rollover Twiddles
    double complex * temp_array;
    temp_array = (double complex * )malloc(current_size*sizeof(double complex));
    for(int i = 0; i < current_size; i++)
        {
            double twid_real = cos((E_PI*2*i*ptr_jump)/total_size);
            double twid_imag = -sin((E_PI*2*i*ptr_jump)/total_size);
            double complex twiddle_factor = twid_real + I*twid_imag;

            if(i==0){
               temp_array[i] = bins[left+i] + 1*bins[left+current_size/2+i];
            } 
            else if(i<current_size/2)
            {
               temp_array[i] = bins[left+i] + twiddle_factor*bins[left+current_size/2+i];
            }
            else
            {
                temp_array[i] = bins[left+i] + twiddle_factor*bins[left-(current_size)/2+i];
            }
                    
        }
        for(int k = 0; k < current_size;k++)
        {
        bins[left+k] = temp_array[k];
        bin_check[left+k] = cabs(bins[k+left]);

        }
    if(temp_array){free(temp_array);}
    
    }
    
    //Now need to join values and bubble up;
    return 1;
}
*/
//TRYING AN IN PLACE FFT, THIS WASN'T WORKING SO I WILL COME BACK TO IT ONCE I GET AN FFT WORKING.



int fft_algorithm(double * arr,complex double *bins, int index,int current_size, int total_size)
{
    if(current_size == 1) return 1; //base case
    int next_size = current_size/2;
    int ptr_jump = total_size/current_size;
    int bindex; //INDEX OF BINS
    complex double * even_bin = (complex double * )malloc(next_size*sizeof(complex double));
    complex double * odd_bin = (complex double * )malloc(next_size*sizeof(complex double));
    fft_algorithm(arr,even_bin,index,next_size,total_size);
    fft_algorithm(arr,odd_bin,index+ptr_jump,next_size,total_size);
    

   // printf("INDEX %d",index);
    //printf("bindex = %d\n");

    if(current_size ==2)printf("index: %d and first value: %f, index %d and second value %f \n",index,arr[index],(index+ptr_jump),arr[index+ptr_jump]); //testing if in place split works
    if(current_size ==2) //BASE CASE where Wn is easy
    {
        bindex = index%2==0 ? index:index+current_size+1; // INDEX FOR THE BIN OUTPUT;
        bins[0] = arr[index] + arr[index+ptr_jump];
        bins[1] = arr[index] - arr[index+ptr_jump];
        bin_check[bindex] = arr[index] + arr[index+ptr_jump];
        bin_check[bindex+1] = arr[index] - arr[index+ptr_jump];
    }
    else
    {
    complex double * temp_array;
    temp_array = (complex double * )malloc(current_size*sizeof(complex double));
    int ptr_jump = total_size/current_size; // NEEDED FOR Wn
    for(int l= 0; l < current_size/2;l++)
        {
        bin_check[l] = cabs(even_bin[l]);
        bin_check[l+2] = cabs(odd_bin[l+2]);
        }
    for(int i = 0; i < current_size; i++)
        {
            if(i==0){
               temp_array[i] = even_bin[i] + 1*odd_bin[i];
            } 
            else
            {
                double twid_real = cos((E_PI*2*i*ptr_jump)/total_size);
                double twid_imag = -sin((E_PI*2*i*ptr_jump)/total_size);
                complex double twiddle_factor = twid_real + I*twid_imag;
                if(i<current_size/2)
                {
                temp_array[i] = even_bin[i] + twiddle_factor*odd_bin[i];
                }
                else
                {
                temp_array[i] = odd_bin[-(current_size)/2+i] + twiddle_factor*even_bin[-(current_size)/2+i];
                }
            }
                    
        }
        for(int k = 0; k < current_size;k++)
        {
        bins[k] = temp_array[k];
        bin_check[k] = cabs(bins[k]);
        }
    free(temp_array);
    }
    free(even_bin);
    free(odd_bin);
    //Now need to join values and bubble up;
    return 1;
}

