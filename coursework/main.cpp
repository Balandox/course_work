#define ARGCOUNT 4
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "AssignmentP.h"


int main(int argc, char* argv[])
{
    std::string InputFile, OutputFile, Alg;
    if (argc == ARGCOUNT) {
        InputFile = argv[1];
        OutputFile = argv[2];
        Alg = argv[3];
    }
    else {
        std::cout << "\nIncorrect input parameters!Try again";
        return - 1;
    }
    
    AssignmentP solve;
    try {
        solve.load(InputFile);
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << " Try again.";
    }
   
    try { 
        solve.InputValidation(); 
    }
    catch (std::invalid_argument& e){
        std::cout << e.what() << " Try again.";
        return -1;
    }

    if (Alg == "GreedyAlgorithm")
        solve.GreedyAlg();
    else if (Alg == "BruteForce")
        solve.BR();
    else {
        std::cout << "\nIncorrect name of algorithm!\nChoose GreedyAlgorithm or BruteForce.\nTry again!\n";
        return -1;
    }
    try {
        solve.save(OutputFile);
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << " Try again.";
    }
    return 0;
}



