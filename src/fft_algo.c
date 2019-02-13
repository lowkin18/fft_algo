

//only RADIX 2 sizing capable need to make modifications if using variable size sample
// trying to implement the algorithm as inplace and bubble up amounts

#include "fft_algo.h"



//LOOK UP ARRAYS TO PUT THE SAMPLES IN REVERSE BIT ORDER

#if 1
double bin_check[ARR_SIZE] = {0,0,0,0,0,0,0,0};

int bit_r_8[8] = {0 ,4 ,2 ,6 ,1 ,5 ,3 ,7};
int bit_r_16[16] = {0 ,8 ,4 ,12 ,2 ,10 ,6 ,14 ,1 ,9 ,5 ,13 ,3 ,11 ,7 ,15};
int bit_r_32[32] = {0 ,16 ,8 ,24 ,4 ,20 ,12 ,28 ,2 ,18 ,10 ,26 ,6 ,22 ,14 ,30 ,1 ,17 ,9 ,25 ,5 ,21 ,13 ,29 ,3 ,19 ,11 ,27 ,7 ,23 ,15 ,31};
int bit_r_64[64] = {0 ,32 ,16 ,48 ,8 ,40 ,24 ,56 ,4 ,36 ,20 ,52 ,12 ,44 ,28 ,60 ,2 ,34 ,18 ,50 ,10 ,42 ,26 ,58 ,6 ,38 ,22 ,54 ,14 ,46 ,30 
,62 ,1 ,33 ,17 ,49 ,9 ,41 ,25 ,57 ,5 ,37 ,21 ,53 ,13 ,45 ,29 ,61 ,3 ,35 ,19 ,51 ,11 ,43 ,27 ,59 ,7 ,39 ,23 ,55 ,15 ,47 ,31 ,63 };

int bit_r_128[128] = {0 ,64 ,32 ,96 ,16 ,80 ,48 ,112 ,8 ,72 ,40 ,104 ,24 ,88 ,56 ,120 ,4 ,68 ,36 ,100 ,20 ,84 ,52 ,116 ,12 ,76 ,44 ,108 
,28 ,92 ,60 ,124 ,2 ,66 ,34 ,98 ,18 ,82 ,50 ,114 ,10 ,74 ,42 ,106 ,26 ,90 ,58 ,122 ,6 ,70 ,38 ,102 ,22 ,86 ,54 ,118 ,14 ,78 ,46 ,110 ,30 
,94 ,62 ,126 ,1 ,65 ,33 ,97 ,17 ,81 ,49 ,113 ,9 ,73 ,41 ,105 ,25 ,89 ,57 ,121 ,5 ,69 ,37 ,101 ,21 ,85 ,53 ,117 ,13 ,77 ,45 ,109 ,29 ,93 ,61 
,125 ,3 ,67 ,35 ,99 ,19 ,83 ,51 ,115 ,11 ,75 ,43 ,107 ,27 ,91 ,59 ,123 ,7 ,71 ,39 ,103 ,23 ,87 ,55 ,119 ,15 ,79 ,47 ,111 ,31 ,95 ,63 ,127};


int bit_r_256[256] = {};
int bit_r_512[512] = {};
int bit_r_1024[1024] = {0 ,512 ,256 ,768 ,128 ,640 ,384 ,896 ,64 ,576 ,320 ,832 ,192 ,704 ,448 ,960 ,32 ,544 ,288 ,800 ,160 ,672 ,416 ,928 ,96 ,608 ,352 ,864 ,224 ,736 ,480 ,992 ,16 
,528 ,272 ,784 ,144 ,656 ,400 ,912 ,80 ,592 ,336 ,848 ,208 ,720 ,464 ,976 ,48 ,560 ,304 ,816 ,176 ,688 ,432 ,944 ,112 ,624 ,368 ,880 ,240 ,752 ,496 ,1008 ,8 ,520 ,264 ,776 ,136 ,648 ,392 ,904 ,72 ,584 ,328
,840 ,200 ,712 ,456 ,968 ,40 ,552 ,296 ,808 ,168 ,680 ,424 ,936 ,104 ,616 ,360 ,872 ,232 ,744 ,488 ,1000 ,24 ,536 ,280 ,792 ,152 ,664 ,408 ,920 ,88 ,600 ,344 ,856 ,216 ,728 ,472 ,984 
,56 ,568 ,312 ,824 ,184 ,696 ,440 ,952 ,120 ,632 ,376 ,888 ,248 ,760 ,504 ,1016 ,4 ,516 ,260 ,772 ,132 ,644 ,388 ,900 ,68 ,580 ,324 ,836 ,196 ,708 ,452 ,964 ,36 ,548 ,292 ,804 ,164
,676 ,420 ,932 ,100 ,612 ,356 ,868 ,228 ,740 ,484 ,996 ,20 ,532 ,276 ,788 ,148 ,660 ,404 ,916 ,84 ,596 ,340 ,852 ,212 ,724 ,468 ,980 ,52 ,564 ,308 ,820 ,180 ,692 ,436 ,948 ,116 ,628
,372 ,884 ,244 ,756 ,500 ,1012 ,12 ,524 ,268 ,780 ,140 ,652 ,396 ,908 ,76 ,588 ,332 ,844 ,204 ,716 ,460 ,972 ,44 ,556 ,300 ,812 ,172 ,684 ,428 ,940 ,108 ,620 ,364 ,876 ,236 ,748 ,492
 ,1004 ,28 ,540 ,284 ,796 ,156 ,668 ,412 ,924 ,92 ,604 ,348 ,860 ,220 ,732 ,476 ,988 ,60 ,572 ,316 ,828 ,188 ,700 ,444 ,956 ,124 ,636 ,380 ,892 ,252 ,764 ,508 ,1020 ,2 ,514 ,258 ,770 
 ,130 ,642 ,386 ,898 ,66 ,578 ,322 ,834 ,194 ,706 ,450 ,962 ,34 ,546 ,290 ,802 ,162 ,674 ,418 ,930 ,98 ,610 ,354 ,866 ,226 ,738 ,482 ,994 ,18 ,530 ,274 ,786 ,146 ,658 ,402 ,914 ,82 ,594
  ,338 ,850 ,210 ,722 ,466 ,978 ,50 ,562 ,306 ,818 ,178 ,690 ,434 ,946 ,114 ,626 ,370 ,882 ,242 ,754 ,498 ,1010 ,10 ,522 ,266 ,778 ,138 ,650 ,394 ,906 ,74 ,586 ,330 ,842 ,202 ,714
,458 ,970 ,42 ,554 ,298 ,810 ,170 ,682 ,426 ,938 ,106 ,618 ,362 ,874 ,234 ,746 ,490 ,1002 ,26 ,538 ,282 ,794 ,154 ,666 ,410 ,922 ,90 ,602 ,346 ,858 ,218 ,730 ,474 ,986 ,58 ,570 ,314
,826 ,186 ,698 ,442 ,954 ,122 ,634 ,378 ,890 ,250 ,762 ,506 ,1018 ,6 ,518 ,262 ,774 ,134 ,646 ,390 ,902 ,70 ,582 ,326 ,838 ,198 ,710 ,454 ,966 ,38 ,550 ,294 ,806 ,166 ,678 ,422 ,934
,102 ,614 ,358 ,870 ,230 ,742 ,486 ,998 ,22 ,534 ,278 ,790 ,150 ,662 ,406 ,918 ,86 ,598 ,342 ,854 ,214 ,726 ,470 ,982 ,54 ,566 ,310 ,822 ,182 ,694 ,438 ,950 ,118 ,630 ,374 ,886 ,246
,758 ,502 ,1014 ,14 ,526 ,270 ,782 ,142 ,654 ,398 ,910 ,78 ,590 ,334 ,846 ,206 ,718 ,462 ,974 ,46 ,558 ,302 ,814 ,174 ,686 ,430 ,942 ,110 ,622 ,366 ,878 ,238 ,750 ,494 ,1006 ,30 ,542 
,286 ,798 ,158 ,670 ,414 ,926 ,94 ,606 ,350 ,862 ,222 ,734 ,478 ,990 ,62 ,574 ,318 ,830 ,190 ,702 ,446 ,958 ,126 ,638 ,382 ,894 ,254 ,766 ,510 ,1022 ,1 ,513 ,257 ,769 ,129 ,641 ,385 
,897 ,65 ,577 ,321 ,833 ,193 ,705 ,449 ,961 ,33 ,545 ,289 ,801 ,161 ,673 ,417 ,929 ,97 ,609 ,353 ,865 ,225 ,737 ,481 ,993 ,17 ,529 ,273 ,785 ,145 ,657 ,401 ,913 ,81 ,593 ,337 ,849 ,209
 ,721 ,465 ,977 ,49 ,561 ,305 ,817 ,177 ,689 ,433 ,945 ,113 ,625 ,369 ,881 ,241 ,753 ,497 ,1009 ,9 ,521 ,265 ,777 ,137 ,649 ,393 ,905 ,73 ,585 ,329 ,841 ,201 ,713 ,457 ,969 ,41 ,553 ,297 
 ,809 ,169 ,681 ,425 ,937 ,105 ,617 ,361 ,873 ,233 ,745 ,489 ,1001 ,25 ,537 ,281 ,793 ,153 ,665 ,409 ,921 ,89 ,601 ,345 ,857 ,217 ,729 ,473 ,985 ,57 ,569 ,313 ,825 ,185 ,697 ,441 ,953 
 ,121 ,633 ,377 ,889 ,249 ,761 ,505 ,1017 ,5 ,517 ,261 ,773 ,133 ,645 ,389 ,901 ,69 ,581 ,325 ,837 ,197 ,709 ,453 ,965 ,37 ,549 ,293 ,805 ,165 ,677 ,421 ,933 ,101 ,613 ,357 ,869 ,229 
 ,741 ,485 ,997 ,21 ,533 ,277 ,789 ,149 ,661 ,405 ,917 ,85 ,597 ,341 ,853 ,213 ,725 ,469 ,981 ,53 ,565 ,309 ,821 ,181 ,693 ,437 ,949 ,117 ,629 ,373 ,885 ,245 ,757 ,501 ,1013
,13 ,525 ,269 ,781 ,141 ,653 ,397 ,909 ,77 ,589 ,333 ,845 ,205 ,717 ,461 ,973 ,45 ,557 ,301 ,813 ,173 ,685 ,429 ,941 ,109 ,621 ,365 ,877 ,237 ,749 ,493 ,1005 ,29 ,541 ,285 ,797 ,157
,669 ,413 ,925 ,93 ,605 ,349 ,861 ,221 ,733 ,477 ,989 ,61 ,573 ,317 ,829 ,189 ,701 ,445 ,957 ,125 ,637 ,381 ,893 ,253 ,765 ,509 ,1021 ,3 ,515 ,259 ,771 ,131 ,643 ,387 ,899 ,67 ,579 
,323 ,835 ,195 ,707 ,451 ,963 ,35 ,547 ,291 ,803 ,163 ,675 ,419 ,931 ,99 ,611 ,355 ,867 ,227 ,739 ,483 ,995 ,19 ,531 ,275 ,787 ,147 ,659 ,403 ,915 ,83 ,595 ,339 ,851 ,211 ,723 ,467 
,979 ,51 ,563 ,307 ,819 ,179 ,691 ,435 ,947 ,115 ,627 ,371 ,883 ,243 ,755 ,499 ,1011 ,11 ,523 ,267 ,779 ,139 ,651 ,395 ,907 ,75 ,587 ,331 ,843 ,203 ,715 ,459 ,971 ,43 ,555 ,299 ,811 
,171 ,683 ,427 ,939 ,107 ,619 ,363 ,875 ,235 ,747 ,491 ,1003 ,27 ,539 ,283 ,795 ,155 ,667 ,411 ,923 ,91 ,603 ,347 ,859 ,219 ,731 ,475 ,987 ,59 ,571 ,315 ,827 ,187 ,699 ,443 ,955 ,123 
,635 ,379 ,891 ,251 ,763 ,507 ,1019 ,7 ,519 ,263 ,775 ,135 ,647 ,391 ,903 ,71 ,583 ,327 ,839 ,199 ,711 ,455 ,967 ,39 ,551 ,295 ,807 ,167 ,679 ,423 ,935 ,103 ,615 ,359 ,871 ,231 ,743 
,487 ,999 ,23 ,535 ,279 ,791 ,151 ,663 ,407 ,919 ,87 ,599 ,343 ,855 ,215 ,727 ,471 ,983 ,55 ,567 ,311 ,823 ,183 ,695 ,439 ,951 ,119 ,631 ,375 ,887 ,247 ,759 ,503 ,1015 ,15 ,527 ,271 
,783 ,143 ,655 ,399 ,911 ,79 ,591 ,335 ,847 ,207 ,719 ,463 ,975 ,47 ,559 ,303 ,815 ,175 ,687 ,431 ,943 ,111 ,623 ,367 ,879 ,239 ,751 ,495 ,1007 ,31 ,543 ,287 ,799 ,159 ,671 ,415 ,927
,95 ,607 ,351 ,863 ,223 ,735 ,479 ,991 ,63 ,575 ,319 ,831 ,191 ,703 ,447 ,959 ,127 ,639 ,383 ,895 ,255 ,767 ,511 ,1023};

#endif 


/**
 * @brief 
 * 
 * @param arr 
 * @param size 
 */
void FFT_order_array(double arr[],int size)
{
    double complex temp_array[1024];
    for(int i = 0; i < size ;i++)
    {
        temp_array[i] = arr[bit_r_1024[i]];
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






/*

TRYING AN IN PLACE FFT, THIS WASN'T WORKING SO I WILL COME BACK TO IT ONCE I GET AN FFT WORKING.



int fft_algorithm(double * arr,double complex *bins, int index,int right, int total_size)
{
    if(current_size == 1) return 1; //base case
    int next_size = current_size/2;
    int ptr_jump = total_size/current_size;
    int bindex; //INDEX OF BINS

    fft_algorithm(arr,bins,index,next_size,total_size);
    fft_algorithm(arr,bins,index+ptr_jump,next_size,total_size);
    
    bindex = index%2==0 ? index:index+1; // INDEX FOR THE BIN OUTPUT;
   // printf("INDEX %d",index);
    //printf("bindex = %d\n");

    if(current_size ==2)printf("index: %d and first value: %f, index %d and second value %f \n",index,arr[index],(index+ptr_jump),arr[index+ptr_jump]); //testing if in place split works
    if(current_size ==2) //BASE CASE where Wn is easy
    {
        bindex = index%2==0 ? index:index+current_size+1; // INDEX FOR THE BIN OUTPUT;
        bins[bindex] = arr[index] + arr[index+ptr_jump];
        bins[bindex+1] = arr[index] - arr[index+ptr_jump];
        bin_check[bindex] = arr[index] + arr[index+ptr_jump];
        bin_check[bindex+1] = arr[index] - arr[index+ptr_jump];
    }
    else
    {
    int iMult = 1; // index multiplier to match bins going forward and rap around
    int h_ptr_j = ptr_jump/2; // INDEX multiplier to match G(k) + Twiddle * H(k)
    
    for(int i = 0; i < current_size; i++)
        {
            double complex twiddle_factor = cos((E_PI*i*ptr_jump)/current_size) - I*sin((E_PI*i*ptr_jump)/current_size);
            if(i>=current_size/2) iMult =-1;
            if(i==0){
               bins[bindex+i] = bins[bindex+i] + 1*bins[bindex+ptr_jump*iMult];
            } 
            else
            {
               bins[bindex+i] = bins[bindex+i] + twiddle_factor*bins[bindex+i+ptr_jump*iMult];
            }         
        }
        for(int k = 0; k < current_size;k++)
        {
        bin_check[k] = cabs(bins[k]);
        }
    }
    
    //Now need to join values and bubble up;
    return 1;
}

*/