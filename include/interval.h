#pragma once 
class interval {
    private:
        double min; 
        double max;
    public:
        interval(double _min, double _max): min(_min), max(_max) {}
        bool contains(double x) {
            if(x<=min || x >=max) {return false;}
            else {return true; }
        }
        bool surrounds(double x) {
            if(x<min || x >max) {return false;}
            else {return true; }
        }
        double clamp(double x) {
            if(x < min) {return min; }
            else if(x > max) {return max; }
            else {return x;} 
        }
        void update_max(double m){ max = m; }
        void update_min(double m){ min = m; }
}; 