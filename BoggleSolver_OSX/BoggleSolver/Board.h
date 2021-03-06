//
//  Board.h
//  BoggleSolver
//
//  Created by Vince Lugli on 5/8/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <set>
#include <utility>
#include <fstream>
#include <sstream>

class Dictionary;

class Board
{
public:
    Board();
    ~Board();
    
    void solve();
    void solve(std::string str, std::set<std::pair<int, int>> prevLocations, int row, int col);
    
private:
    std::set<std::string> mFoundWords;
    Dictionary* mDict;
    std::ifstream mBoggleBoardStream;
    std::vector<std::vector<char>> mBoggleBoard;
    int mRows;
    int mCols;
};
