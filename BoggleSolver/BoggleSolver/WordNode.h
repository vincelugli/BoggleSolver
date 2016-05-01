//
//  WordNode.h
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//
#pragma once

#include <unordered_map>

class WordNode
{
public:
    WordNode();
    WordNode(const char* word);
    WordNode(bool isWord);
    ~WordNode();
    
    void addNewWord(const char* word);
    bool isWord(const char* word);
    
private:
    void addLetterToMap(const char* word);
    
    std::unordered_map<char, WordNode*>     mNextLetters;
    bool                                    mIsWord = false;
};
