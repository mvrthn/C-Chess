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

inline void printSquare(Square sq) {
    std::cout << char('a' + (sq % 8)) << 8 - (sq / 8) << "\n";
}

inline void test(const std::string& str) {
    std::cout << str << "\n";
}

}