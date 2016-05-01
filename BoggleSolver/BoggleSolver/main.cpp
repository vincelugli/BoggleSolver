//
//  main.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include <iostream>
#include <string>

#include "WordNode.h"

int main(int argc, const char * argv[]) {
    WordNode testing("ardvark");
    testing.addNewWord("ad");
    
    bool isWord = testing.isWord("ad");
    isWord = testing.isWord("ard5vark");
    
    return 0;
}
