#pragma once


#include <cstdio>
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
    std::cout << char('a' + (sq % 8)) << (sq / 8) + 1;
}

inline void test(const std::string& str) {
    std::cout << str << "\n";
}

inline void print(int x) {
    std::cout << x << "\n";
}

inline void printMove(Square from, Square to) {
    printSquare(from);
    std::cout << " -> ";
    printSquare(to);
    std::cout << "\n";
}

}

inline void printAddr(void* ptr) {
    printf("%d\n", ptr);
}