#include "interval.h"

std::ostream& operator<<(std::ostream&os, const Interval2f& intv){
    os<<"(" <<intv.min<<", "<<intv.max <<")" << std::endl; 
    return os; 
}