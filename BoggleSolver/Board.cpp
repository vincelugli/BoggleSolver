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

Board::Board()
: mDict(new Dictionary())
, mRows(0)
, mCols(0)
{
    mBoggleBoardStream.open("../Random2000x2000.csv", std::ifstream::in);
    
    for (std::string row; std::getline(mBoggleBoardStream, row); )
    {
        std::istringstream rowStream(row);
        std::vector<char> newRow;
        int maxCols = 0;
        for (std::string bogglePiece; std::getline(rowStream, bogglePiece, ','); )
        {
            newRow.push_back(*bogglePiece.c_str());
            ++maxCols;
        }
        mCols = maxCols > mCols ? maxCols : mCols;
        mBoggleBoard.push_back(newRow);
        ++mRows;
    }
    
//     --mCols;
//     --mRows;
    mBoggleBoardStream.close();
}

Board::~Board()
{
    delete mDict;
}

void Board::solve()
{
    std::vector<bool> prevLocations(mBoggleBoard.size() * mBoggleBoard[0].size());
    for (size_t row = 0; row < mBoggleBoard.size(); ++row)
    {
        for(size_t col = 0; col < mBoggleBoard[row].size(); ++col)
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
    
    str += mBoggleBoard[row][col];
    const char* potentialWord = str.c_str();
    prevLocations[mCols*row + col] = true;
    
    if (str.size() >= 3)
    {
        WordResult findResult = mDict->isWord(potentialWord);
        if (findResult == WORD)
        {
            mFoundWords.insert(str);
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

