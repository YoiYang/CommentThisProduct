#include <iostream>
#include <string.h>
#include <sstream>

#include "CommentGenerator.hpp"

using namespace std;

// use ./main
// or
// use ./main datadirecoty/
int main(int argc, const char ** argv) {
    
    CommentGenerator dg;
    
    /*
    if (s.length() > 0) CommentGenerator dg(argv[1]);
    else CommentGenerator dg();
     */
    int minWords = 10;
    while (true){

        cout << "Enter minimum length of comment: ";
        cin >> minWords;
        cout << dg.comment(minWords) << endl;
    }

    return 0;
}
