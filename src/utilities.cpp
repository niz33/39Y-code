#include "main.h"

double Utilities::bound_by(double l,double r,double value){
    value=fmax(l,value);
    value=fmin(r,value);
    return value;
}

double Utilities::drive_control_map(double input){
    if(abs(input)<16){
        return 0.0;
    }
    double ans;
    if(input>0){
        ans= (input-16)/111.0;
    }
    else{
        ans=(input+16)/111.0;
    }
    return ans;
} 
