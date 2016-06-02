//
//  Board.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/8/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include "Board.h"
#include "Dictionary.h"

#include <iostream>

Board::Board(Dictionary& dict)
: mDict(dict)
, mRows(1) // Start at 1 because we start reading at the first row.
, mCols(0)
{
    mFoundWords.reserve(1024);

    std::ifstream boggleBoardStream("../Random100x100.csv", std::ifstream::in);
    boggleBoardStream.seekg(0, boggleBoardStream.end);
    int length = boggleBoardStream.tellg();
    boggleBoardStream.seekg(0, boggleBoardStream.beg);

    mBoggleBoard.reserve(length);

    std::vector<char> buffer;
    buffer.resize(length + 1);
    boggleBoardStream.read(buffer.data(), length);
    buffer[length] = '\0';

    for (int i = 0; i < length; ++i)
    {
        char c = buffer[i];
        if (c >= 'a' && c <= 'z')
        {
            mBoggleBoard.push_back(c);
        }
        else if (c == '\n') 
        {
            ++mRows;
        }
    }

    mCols = mBoggleBoard.size() / mRows;
    boggleBoardStream.close();
}

Board::~Board()
{
}

void Board::solve()
{
    std::vector<bool> prevLocations(mBoggleBoard.size());
    for (size_t row = 0; row < mRows; ++row)
    {
        for(size_t col = 0; col < mCols; ++col)
        {
            std::string str = "";
            solve(str, prevLocations, row, col);
        }
    }
}

void Board::solve(std::string str, std::vector<bool>& prevLocations, int row, int col)
{
    // Early out if current location has been viewed. May want to move this to before function call.
    if (row >= mRows || 
        col >= mCols || 
        col < 0 || 
        row < 0 || 
        prevLocations[mCols*row + col])
    {
        return;
    }
    
    str += mBoggleBoard[mCols*row + col];
    const char* potentialWord = str.c_str();
    prevLocations[mCols*row + col] = true;
    
    if (str.size() >= 3)
    {
        WordResult findResult = mDict.isWord(potentialWord);
        if (findResult == WORD)
        {
            mFoundWords.emplace_back(str);
        }
        else if (findResult == EARLY_OUT)
        {
            // Early out since we hit a leaf node. No possible words past this point.
            prevLocations[mCols*row + col] = false;
            return;
        }
    }
    
    solve(str, prevLocations, row, col + 1);
    solve(str, prevLocations, row, col - 1);
    solve(str, prevLocations, row + 1, col);
    solve(str, prevLocations, row + 1, col + 1);
    solve(str, prevLocations, row + 1, col - 1);
    solve(str, prevLocations, row - 1, col);
    solve(str, prevLocations, row - 1, col + 1);
    solve(str, prevLocations, row - 1, col - 1);
    
    // Finished looking through this point.
    prevLocations[mCols*row + col] = false;
}

