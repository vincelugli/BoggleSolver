//
//  Dictionary.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include "Dictionary.h"
#include "Dictionary.h"

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
        
        
        std::unordered_map<char, Dictionary*>::iterator found = mDictionary.find(*cStrWord);
        if (found == mDictionary.end())
        {
            // New letter
            mDictionary.emplace(cStrWord[0], new Dictionary(cStrWord + 1));
        }
        else
        {
            mDictionary[*cStrWord]->addNewWord(cStrWord + 1);
        }
    }
}

#include <iostream>

#include "Dictionary.h"

Dictionary::Dictionary(bool isWord)
: mIsWord(isWord)
{}

Dictionary::Dictionary(const char* word)
{
    addLetterToMap(word);
}

Dictionary::~Dictionary()
{
    // Clean up all Dictionarys we created.
    for(auto const& nextLetter : mDictionary) {
        delete nextLetter.second;
    }
}

void Dictionary::addNewWord(const char *word)
{
    if (mDictionary.count(word[0]))
    {
        // Letter already exists, pass onto existing Dictionary
        mDictionary[word[0]]->addNewWord(&word[1]);
    }
    else
    {
        addLetterToMap(word);
    }
}

void Dictionary::addLetterToMap(const char* word)
{
    if (word[1])
    {
        mDictionary.emplace(word[0], new Dictionary(word + 1));
    }
    else
    {
        mDictionary.emplace(word[0], new Dictionary(true));
    }
}

bool Dictionary::isWord(const char* word)
{
    std::unordered_map<char, Dictionary*>::iterator found = mDictionary.find(*word);
    if (found == mDictionary.end())
    {
        return *word ? false : mIsWord;
    }
    else
    {
        return mDictionary.at(*word)->isWord(word + 1);
    }
}
