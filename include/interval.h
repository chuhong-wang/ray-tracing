#pragma once 
#include <ostream>

template <typename T> 
class Interval {
    public:
        T min; 
        T max;
        
        Interval(T _min, T _max): min(_min), max(_max) {}

        bool contains(T x) {
            if(x<=min || x >=max) {return false;}
            else {return true; }
        }
        bool surrounds(T x) {
            if(x<min || x >max) {return false;}
            else {return true; }
        }
        T clamp(T x) const {
            if(x < min) {return min; }
            else if(x > max) {return max; }
            else {return x;} 
        }

        void update_max(T m){ max = m; }
        void update_min(T m){ min = m; }

        void combine(const Interval& intv2){
            update_min(fmin(min, intv2.min)); 
            update_max(fmax(max, intv2.max));
        }
}; 

typedef Interval<float> Interval2f; 
typedef Interval<double> Interval2d; 

