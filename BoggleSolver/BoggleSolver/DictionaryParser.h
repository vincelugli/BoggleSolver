//
//  DictionaryParser.h
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//
#pragma once

#include <unordered_map>

class WordNode;

class DictionaryParser
{
public:
    DictionaryParser();
    ~DictinoaryParser();
    
private:
    std::unordered_map<char, WordNode*>    mDictionary;
};