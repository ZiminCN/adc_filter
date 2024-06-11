#include "adc_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALLOW_CREATION_OF_VARIABLE_LENGTH_ARRAYS true

/**
 * @brief this filter is a very simple func, just determine the
 *  upper and lower limits and return the values within the range 
 * 
 * @param max_effective_val 
 * @param min_effective_val 
 * @param input_val 
 * @return float 
 */
float limiting_filter(const float max_effective_val, const float min_effective_val, const float input_val)
{
        float output_val;
        output_val = (input_val > min_effective_val) ? input_val : min_effective_val;
        output_val = (output_val < max_effective_val) ? output_val : min_effective_val;
        return output_val;
}

float median_filter(const int sample_cnt,const float *sample_val)
{
        //! try to create a variable length arrays, but lots of MCU do not supply
#ifdef ALLOW_CREATION_OF_VARIABLE_LENGTH_ARRAYS
        float sample_val_array[sample_cnt];
        memcpy(sample_val_array, sample_val, sample_cnt);
#else
        //! should make sure the size of array is big enough
        float sample_val_array[64];

        if(sample_cnt > sizeof(sample_val_array)){
                return;
        }

        memcpy(sample_val_array, sample_val, sample_cnt);
#endif // ALLOW_CREATION_OF_VARIABLE_LENGTH_ARRAYS

        float temp_val;
        float output_val;

        // bubble sort
        for(int e_cnt = 0; e_cnt < (sample_cnt - 1); e_cnt++){
                for(int i_cnt = 0; i_cnt < (sample_cnt - 1 - e_cnt); i_cnt++){
                        if(sample_val_array[i_cnt] < sample_val_array[i_cnt+1]){
                                temp_val = sample_val_array[i_cnt + 1];
                                sample_val_array[i_cnt + 1] = sample_val_array[i_cnt];
                                sample_val_array[i_cnt] = temp_val;
                        }
                }
        }

        // judge the odd or even num
        if(sample_cnt%2 == 1){
                output_val = sample_val_array[sample_cnt/2];
        }else{
                output_val = (sample_val_array[sample_cnt/2]+sample_val_array[(sample_cnt/2)+1])/2;
        }

        return output_val;
}

float digital_averaging_filter(const int sample_cnt, const float *sample_val)
{
        float sum = 0.0f;
        float output_val;
        
        for(int cnt = 0; cnt < sample_cnt; cnt++){
                sum += sample_val[cnt];
        }

        output_val = sum/sample_cnt;

        return output_val;
}


void median_average_filtering(const int sample_cnt, const float *intput_sample_val, float output_val)
{
        if(sample_cnt < 3){
                return ;
        }

        //! try to create a variable length arrays, but lots of MCU do not supply
#ifdef ALLOW_CREATION_OF_VARIABLE_LENGTH_ARRAYS
        float sample_val_array[sample_cnt];
        memcpy(sample_val_array, intput_sample_val, sample_cnt);
#else
        //! should make sure the size of array is big enough
        float sample_val_array[64];

        if(sample_cnt > sizeof(sample_val_array)){
                return;
        }

        memcpy(sample_val_array, intput_sample_val, sample_cnt);
#endif // ALLOW_CREATION_OF_VARIABLE_LENGTH_ARRAYS

        float temp_val;
        float sum;
        float output_val;

        // bubble sort
        for(int e_cnt = 0; e_cnt < (sample_cnt - 1); e_cnt++){
                for(int i_cnt = 0; i_cnt < (sample_cnt - 1 - e_cnt); i_cnt++){
                        if(sample_val_array[i_cnt] < sample_val_array[i_cnt+1]){
                                temp_val = sample_val_array[i_cnt + 1];
                                sample_val_array[i_cnt + 1] = sample_val_array[i_cnt];
                                sample_val_array[i_cnt] = temp_val;
                        }
                }
        }

        // remove the max num and the min num
        for(int cnt = 0; cnt < (sample_cnt-1); cnt++){
                sum += sample_val_array[cnt+1];
        }

        output_val = sum/(sample_cnt-2);

        return output_val;
}