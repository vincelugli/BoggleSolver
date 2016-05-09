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
    mBoggleBoardStream.open("/Users/vlugli/Git/BoggleSolver/BoggleSolver/BoggleSolver/BoggleSolver/boggle-board.csv", std::ifstream::in);
    
    for (std::string row; std::getline(mBoggleBoardStream, row); )
    {
        std::istringstream rowStream(row);
        std::vector<char> newRow;
        mCols = 0;
        for (std::string bogglePiece; std::getline(rowStream, bogglePiece, ','); )
        {
            newRow.push_back(*bogglePiece.c_str());
            ++mCols;
        }
        mBoggleBoard.push_back(newRow);
        ++mRows;
    }
    
    --mCols;
    --mRows;
    mBoggleBoardStream.close();
}

Board::~Board()
{
    delete mDict;
}

void Board::solve()
{
    for (int row = 0; row < mBoggleBoard.size(); ++row)
    {
        for(int col = 0; col < mBoggleBoard[row].size(); ++col)
        {
            std::string str = "";
            std::set<std::pair<int, int>> prevLocations;
            solve(str, prevLocations, row, col);
        }
    }
}

void Board::solve(std::string str, std::set<std::pair<int, int> > prevLocations, int row, int col)
{
    // Early out if current location has been viewed. May want to move this to before function call.
    std::pair<int, int> newPair = std::make_pair(row, col);
    if (prevLocations.find(newPair) != prevLocations.end())
    {
        return;
    }
    
    str += mBoggleBoard[row][col];
    const char* potentialWord = str.c_str();
    prevLocations.emplace(newPair);
    
    if (prevLocations.size() >= 3)
    {
        WordResult findResult = mDict->isWord(potentialWord);
        if (findResult == WORD)
        {
            if (mFoundWords.find(str) == mFoundWords.end())
            {
                mFoundWords.insert(str);
                std::cout << str << std::endl;
            }
        }
        else if (findResult == EARLY_OUT)
        {
            // Early out since we hit a leaf node. No possible words past this point.
            return;
        }
    }
    
    if (col != mCols)
    {
        solve(str, prevLocations, row, col+1);
        
        if (row != mRows)
        {
            solve(str, prevLocations, row+1, col+1);
        }
        if (row != 0)
        {
            solve(str, prevLocations, row-1, col+1);
        }
    }
    
    if (row != mRows)
    {
        solve(str, prevLocations, row+1, col);
        
        if (col != 0)
        {
            solve(str, prevLocations, row+1, col-1);
        }
    }
    
    
    if (col != 0)
    {
        solve(str, prevLocations, row, col-1);
        
        if (row != 0)
        {
            solve(str, prevLocations, row-1, col-1);
        }
    }
    
    if (row != 0)
    {
        solve(str, prevLocations, row-1, col);
    }
    
    // Finished looking through this point. Remove pair.
    prevLocations.erase(prevLocations.find(newPair));
    str.erase(str.end());
}

