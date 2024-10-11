#include "ClockNative.h"
#include <chrono>

std::any ClockNative::Call(Interpreter* interpreter, const std::vector<std::any>& arguments){
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    double seconds = milliseconds / 1000.0;
    return seconds;
}

int ClockNative::Arity(){
	return 0;
}
