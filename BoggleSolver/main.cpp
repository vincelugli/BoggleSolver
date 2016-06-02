//
//  main.cpp
//  BoggleSolver
//
//  Created by Vince Lugli on 5/1/16.
//  Copyright © 2016 Vince Lugli. All rights reserved.
//

#include "Board.h"
#include "Dictionary.h"

#include <ctime>
#include <iostream>

int main(int argc, const char * argv[]) {
    clock_t startTime = clock();

    Dictionary dict;

    Board boggleBoard(dict);
    
    boggleBoard.solve();

    clock_t endTime = clock();

    double timeToSolve = double(endTime - startTime) / CLOCKS_PER_SEC;

    std::cout << timeToSolve << std::endl;

    std::cout << boggleBoard.GetFoundWordsSize() << std::endl;
    
    return 0;
}
