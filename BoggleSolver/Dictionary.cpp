//
//  Dictionary.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include "Dictionary.h"

#include <fstream>
#include <string>

Dictionary::Dictionary()
{
    std::ifstream filebuffer("../words.txt", std::ifstream::in);
    
    for (std::string word; std::getline(filebuffer, word); )
    {
        bool valid = true;
        for (char c : word)
        {
            if (c < 'a' || c > 'z')
            {
                valid = false;
                break;
            }
        }
        if (!valid || word[0] == '\0')
        {
            continue;
        }
        
        const char* cStrWord = word.c_str();
        
        if (!GetChild(cStrWord[0]))
        {
            // New letter
            GetChild(cStrWord[0]) = new Dictionary(cStrWord + 1);
        }
        else
        {
            GetChild(cStrWord[0])->addNewWord(cStrWord + 1);
        }
    }
}

Dictionary::Dictionary(bool isWord)
: mIsWord(isWord)
{}

Dictionary::Dictionary(const char* word)
{
    addLetterToMap(word);
}

Dictionary::~Dictionary()
{
    // Clean up all Dictionaries we created.
    //for(auto const& nextLetter : mDictionary) {
    //    delete nextLetter;
    //}
}

Dictionary*& Dictionary::GetChild(char c)
{
    if (c < 'a' || c > 'z')
    {
        static int vince = 0;
        ++vince;
    }
    return mDictionary[c - 97];
}

void Dictionary::addNewWord(const char *word)
{
    if (word[0] == '\0')
    {
        return;
    }
    if (GetChild(word[0]))
    {
        // Letter already exists, pass onto existing Dictionary
       GetChild(word[0])->addNewWord(&word[1]);
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
        GetChild(word[0]) = new Dictionary(word + 1);
        ++mDictionarySize;
    }
    else
    {
        GetChild(word[0]) = new Dictionary(true);
        ++mDictionarySize;
    }
}

WordResult Dictionary::isWord(const char* word)
{
    if (word[0] == '\0')
    {
        if (mIsWord)
        {
            mIsWord = false;
            return WORD;
        }
        else
        {
            return NO_WORD;
        }
    }
    if (!GetChild(word[0]))
    {
        // If I still have word left, any possible future words with this prefix are impossible. Return EARLY_OUT
        if (*word)
        {
            return EARLY_OUT;
        }
        
        // If I haven't finished my word, but don't have any place left to go, I'm a leaf and can early out.
        if (!mIsWord && mDictionarySize == 0)
        {
            return EARLY_OUT;
        }
        
        // If I finished my word, check if I'm currently a word or not.
        if (mIsWord)
        {
            mIsWord = false;
            return WORD;
        }
        else
        {
            return NO_WORD;
        }
    }
    else
    {
        return GetChild(word[0])->isWord(word + 1);
    }
}
