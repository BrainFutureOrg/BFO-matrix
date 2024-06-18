//
// Created by kosenko on 18.06.24.
//

#include "color_gradient.h"
#include <stdlib.h>

int* color_gradient_get(color_gradient_settings settings, double position){
    int* rgb = malloc(3* sizeof(int));
    int position_after=0;
    for(int i=0; i<settings.len; i++){
        if(position<=settings.positions[i]){
            position_after = i;
            break;
        }
    }
    if(position_after==0){
        rgb[0] = settings.colors[0][0];
        rgb[1] = settings.colors[0][1];
        rgb[2] = settings.colors[0][2];
    }else{
        double interval = settings.positions[position_after]-settings.positions[position_after-1];
        double before_norm = (position-settings.positions[position_after-1])/interval;
        rgb[0] = (int)(settings.colors[position_after-1][0]*(1-before_norm)+settings.colors[position_after][0]*before_norm);
        rgb[1] = (int)(settings.colors[position_after-1][1]*(1-before_norm)+settings.colors[position_after][1]*before_norm);
        rgb[2] = (int)(settings.colors[position_after-1][2]*(1-before_norm)+settings.colors[position_after][2]*before_norm);
    }
    return rgb;
}