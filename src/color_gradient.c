//
// Created by kosenko on 18.06.24.
//

#include "color_gradient.h"
#include <stdlib.h>

int* color_gradient_get_general(color_gradient_settings settings, double position, color_interpolator interpolator){
    int position_after=0;
    for(int i=0; i<settings.len; i++){
        if(position<=settings.positions[i]){
            position_after = i;
            break;
        }
    }
    if(position_after==0){
        int* rgb = malloc(3* sizeof(int));
        rgb[0] = settings.colors[0][0];
        rgb[1] = settings.colors[0][1];
        rgb[2] = settings.colors[0][2];
        return rgb;
    }else{
        double interval = settings.positions[position_after]-settings.positions[position_after-1];
        double before_norm = (position-settings.positions[position_after-1])/interval;
        return interpolator(settings.colors[position_after-1], settings.colors[position_after], before_norm);
    }
}

int* linear_color_interpolator(int* rgb1, int* rgb2, double position){
    int* rgb = malloc(3* sizeof(int));
    rgb[0] = (int)(rgb1[0]*(1-position)+rgb2[0]*position);
    rgb[1] = (int)(rgb1[1]*(1-position)+rgb2[1]*position);
    rgb[2] = (int)(rgb1[2]*(1-position)+rgb2[2]*position);
    return rgb;
}

int* color_gradient_get(color_gradient_settings settings, double position){
    return color_gradient_get_general(settings, position, linear_color_interpolator);
}