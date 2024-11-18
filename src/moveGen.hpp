#pragma once


#include <algorithm>

#include "types.hpp"
#include "position.hpp"


namespace Chess {

#define MAX_MOVES 256

Move* generate(const Position&, Move*);

class MoveList {
public:
    explicit MoveList(const Position& pos): last(generate(pos, list)) {};

    inline const Move* begin() const { return list; };
    inline const Move* end() const { return last; };
    inline int size() const { return last - list; };

    bool contains(Move move) const { return std::find(begin(), end(), move) != end(); };

private:
    Move list[MAX_MOVES];
    Move* last;
};

}