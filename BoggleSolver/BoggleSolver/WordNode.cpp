//
//  WordNode.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include <iostream>

#include "WordNode.h"

WordNode::WordNode()
: mIsWord(true)
{}

WordNode::WordNode(const char* word)
{
    addLetterToMap(word);
}

WordNode::~WordNode()
{
    // Clean up all WordNodes we created.
    for(auto const& nextLetter : mNextLetters) {
        delete nextLetter.second;
    }
}

void WordNode::addNewWord(const char *word)
{
    if (mNextLetters.count(word[0]))
    {
        // Letter already exists, pass onto existing WordNode
        mNextLetters[word[0]]->addNewWord(&word[1]);
    }
    else
    {
        addLetterToMap(word);
    }
}

void WordNode::addLetterToMap(const char* word)
{
    if (word[1])
    {
        mNextLetters.emplace(word[0], new WordNode(word + 1));
    }
    else
    {
        mNextLetters.emplace(word[0], new WordNode());
    }
}

bool WordNode::isWord(const char* word)
{
    std::unordered_map<char, WordNode*>::iterator found = mNextLetters.find(*word);
    if (found == mNextLetters.end())
    {
        return *word ? false : mIsWord;
    }
    else
    {
        return mNextLetters.at(*word)->isWord(word + 1);
    }
}
