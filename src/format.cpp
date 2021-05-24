#include <string>

#include "format.h"

using std::string;
using std::to_string;

string Format::ZeroPadding(string val){
    val.insert(val.begin(),2-val.size(),0);
    return val;
}
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int seconds) { 
    string HH=to_string(seconds/3600);
    string MM=to_string(seconds%3600/60);
    string SS=to_string(seconds%3600%60);
    string format_time = ZeroPadding(HH)+":"+ZeroPadding(MM)+":"+ZeroPadding(SS);
    return format_time;
}
