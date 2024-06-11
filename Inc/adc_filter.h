#pragma once
#ifndef __ADC_FILTER_H
#define __ADC_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

float limiting_filter(const float max_effective_val, const float min_effective_val, const float input_val);
float median_filter(const int sample_cnt,const float *sample_val);
float digital_averaging_filter(const int sample_cnt, const float *sample_val);
void median_average_filtering(const int sample_cnt, const float *intput_sample_val, float output_val);



#ifdef __cplusplus
}
#endif

#endif __ADC_FILTER_H