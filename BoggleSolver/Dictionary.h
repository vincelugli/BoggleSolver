//
//  DictionaryParser.h
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//
#pragma once

#include <unordered_map>

enum WordResult
{
    EARLY_OUT,
    WORD,
    NO_WORD
};

class Dictionary
{
public:
    Dictionary();
    Dictionary(const char* word);
    Dictionary(bool isWord);
    ~Dictionary();
    
    void addNewWord(const char* word);
    WordResult isWord(const char* word);
    
private:
    void addLetterToMap(const char* word);
    Dictionary*& GetChild(char c);

    int           mDictionarySize = 0;
    Dictionary*   mDictionary[26] = {};
    bool          mIsWord = false;
};
