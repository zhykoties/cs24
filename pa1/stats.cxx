// stats.cxx - implements statistician class as defined in stats.h
// Yunkai Zhang, 4/15/2017

#include <cassert>  // provides assert
#include <limits>
#include "stats.h"  // defines what must be implemented

namespace main_savitch_2C
{
    statistician::statistician()
    // Postcondition: The object has been initialized, and is ready to accept
    // a sequence of numbers. Various statistics will be calculated about the
    // sequence.
    {
        count = 0;
        total = 0;
        tiniest = 0;
        largest = 0;
    }

    void statistician::next(double r)
    // Postcondition: One more number is added to the sequence.
    {
        count++;
        total += r;
        if(count == 1){
            tiniest = r;
            largest = r;
        }
        if(tiniest > r){
            tiniest = r;
        }
        if(largest < r){
            largest = r;
        }
    }

    void statistician::reset()
    // Postcondition: The statistician has been cleared, as if no numbers had
    // yet been given to it.
    {
        count = 0;
        total = 0;
        tiniest = 0;
        largest = 0;
    }

    double statistician::mean( ) const
    //Precondition: length( ) > 0
    //Postcondition: The return value is the arithmetic mean (i.e., the
    //average of all the numbers in the statistician's sequence).
    {
        assert(length()>0);
        return total*1.0/count;
    }

    double statistician::minimum( ) const
    //Precondition: length( ) > 0
    //Postcondition: The return value is the tiniest number in the
    //statistician's sequence.
    {
        assert(length()>0);
        return tiniest;
    }

    double statistician::maximum( ) const
    //Precondition: length( ) > 0
    //Postcondition: The return value is the largest number in the
    //statistician's sequence.
    {
        assert(length()>0);
        return largest;
    }

    statistician operator +(const statistician& s1, const statistician& s2)
    //Postcondition: The statistician that is returned contains all the
    //numbers of the sequences of s1 and s2.
    {
        statistician s3 = statistician();
        s3.count = s1.count + s2.count;
        s3.total = s1.total + s2.total;
        if(s1.tiniest < s2.tiniest){
            s3.tiniest = s1.tiniest;
        }else{
            s3.tiniest = s2.tiniest;
        }
        if(s1.largest > s2.largest){
            s3.largest = s1.largest;
        }else{
            s3.largest = s2.largest;
        }
        return s3;
    }

    statistician operator *(double scale, const statistician& s)
    //Postcondition: The statistician that is returned contains the same
    //numbers that s does, but each number has been multiplied by the
    //scale number.
    {
        statistician s1 = statistician();
        s1.count = s.count;
        s1.total = scale * s.total;
        if(scale < 0){
            s1.tiniest = s.largest * scale;
            s1.largest = s.tiniest * scale;
        }else{
            s1.largest = s.largest * scale;
            s1.tiniest = s.tiniest * scale;
        }
        return s1;
    }

    bool operator ==(const statistician& s1, const statistician& s2){
        if(s1.length() == s2.length()){
            return true;
        }
        if(s1.length() == s2.length() && s1.sum() == s2.sum() && s1.mean() == s2.mean() && s1.minimum() == s2.minimum() && s1.maximum() == s2.maximum()){
            return true;
        }
        return false;
    }
}
