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
    filebuffer.seekg(0, filebuffer.end);
    int length = filebuffer.tellg();
    filebuffer.seekg(0, filebuffer.beg);

    std::vector<char> buffer;
    buffer.resize(length + 1);
    filebuffer.read(buffer.data(), length);
    buffer[length] = '\0';

    int start = 0;
    int end = 0;

    for (int i = 0; i < length; ++i)
    {
        start = i;
        while (i < length && (buffer[i] != '\n' && buffer[i] != '\r'))
        {
            ++i;
        }
        end = i;
        if (start == end)
        {
            continue;
        }

        if (!GetChild(buffer[start]))
        {
            // New Letter
            GetChild(buffer[start]) = new Dictionary(start + 1, end, buffer);
        }
        else
        {
            GetChild(buffer[start])->addNewWord(start + 1, end, buffer);
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

Dictionary::Dictionary(int start, int end, const std::vector<char>& buffer)
{
    Dictionary* curr = this;
    Dictionary* next;
    while (start + 1 < end)
    {
        next = new Dictionary(false);
        curr->GetChild(buffer[start]) = next;
        curr = next;
        ++start;
    }
    curr->GetChild(buffer[start]) = new Dictionary(true);
}

Dictionary::~Dictionary()
{
}

Dictionary*& Dictionary::GetChild(char c)
{
    return mDictionary[c - 97];
}

void Dictionary::addNewWord(int start, int end, const std::vector<char>& buffer)
{
    Dictionary* curr = this;
    while (start + 1 < end)
    {
        if (!curr->GetChild(buffer[start]))
        {
            // New Letter
            GetChild(buffer[start]) = new Dictionary(start + 1, end, buffer);
            return;
        }
        curr = curr->GetChild(buffer[start]);
        ++start;
    }

    if (!curr->GetChild(buffer[start]))
    {
        curr->GetChild(buffer[start]) = new Dictionary(true);
    }
    else
    {
        curr->GetChild(buffer[start])->mIsWord = true;
    }
//     if (start + 1 == end)
//     {
//         GetChild(buffer[start]) = new Dictionary(true);
//         return;
//     }
//     if (!GetChild(buffer[start]))
//     {
//         // New Letter
//         GetChild(buffer[start]) = new Dictionary(start + 1, end, buffer);
//     }
//     else
//     {
//         GetChild(buffer[start])->addNewWord(start + 1, end, buffer);
//     }
}

void Dictionary::addNewWord(const char *word)
{
    if (word[0] == '\0' || word[0] == '\n' || word[0] == '\r')
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
