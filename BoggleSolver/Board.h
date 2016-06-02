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
    Board(Dictionary& dict);
    ~Board();
    
    void solve();
    void solve(std::string str, std::vector<bool>& prevLocations, int row, int col);

    size_t GetFoundWordsSize() const { return mFoundWords.size(); }
    
private:
    std::vector<std::string> mFoundWords;
    Dictionary& mDict;
    std::vector<char> mBoggleBoard;
    int mRows;
    int mCols;
};
