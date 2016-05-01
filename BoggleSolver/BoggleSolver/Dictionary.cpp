//
//  Dictionary.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include "Dictionary.h"
#include "WordNode.h"

#include <fstream>
#include <string>

#include <iostream>

Dictionary::Dictionary()
{
    std::ifstream filebuffer("/Users/vlugli/Git/BoggleSolver/BoggleSolver/BoggleSolver/english-words.20", std::ifstream::in);
    
    for (std::string word; std::getline(filebuffer, word); )
    {
        // Remove end of line character (\r)
        word.erase(word.end() - 1);
        const char* cStrWord = word.c_str();
        
        
        std::unordered_map<char, WordNode*>::iterator found = mDictionary.find(*cStrWord);
        if (found == mDictionary.end())
        {
            // New letter
            mDictionary.emplace(cStrWord[0], new WordNode(cStrWord + 1));
        }
        else
        {
            mDictionary[*cStrWord]->addNewWord(cStrWord + 1);
        }
    }
}

bool Dictionary::isWord(const char *word)
{
    std::unordered_map<char, WordNode*>::iterator found = mDictionary.find(*word);
    if (found == mDictionary.end())
    {
        return false;
    }
    else
    {
        return mDictionary.at(*word)->isWord(word + 1);
    }
}