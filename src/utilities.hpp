#pragma once


#include <iostream>


namespace Chess {

inline void error(const std::string& funcName, int errNum, unsigned char token = 0) {
    std::cerr << "Error in " << funcName << ": " << errNum;
    if(token) {
        std::cerr << " = " << token;
    }
    std::cerr << "\n";
    exit(-1);
}

}