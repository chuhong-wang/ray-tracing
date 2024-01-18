#pragma once 
#include <ostream>
class Interval {
    public:
        double min; 
        double max;
        
        Interval(double _min, double _max): min(_min), max(_max) {}

        // double upperbound() {return max; }
        // double lowerbound() {return min; }

        bool contains(double x) {
            if(x<=min || x >=max) {return false;}
            else {return true; }
        }
        bool surrounds(double x) {
            if(x<min || x >max) {return false;}
            else {return true; }
        }
        double clamp(double x) const {
            if(x < min) {return min; }
            else if(x > max) {return max; }
            else {return x;} 
        }

        void update_max(double m){ max = m; }
        void update_min(double m){ min = m; }

        void combine(const Interval& intv2){
            update_min(fmin(min, intv2.min)); 
            update_max(fmax(max, intv2.max));
        }
}; 

std::ostream& operator<<(std::ostream&os, const Interval& intv){
    os<<"(" <<intv.min<<", "<<intv.max <<")" << std::endl; 
    return os; 
}