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
    cout << "Welcome to a random comment generator, on musical instruments." << endl;
    /*
    if (s.length() > 0) CommentGenerator dg(argv[1]);
    else CommentGenerator dg();
     */
    int minWords = 10;
    while (true){
        cout << "**********************************\n";
        cout << "Enter the number of words: ";
        cin >> minWords;
        if(!cin){
            cout << "quitting.. ";
            break;
        }
        cout << dg.comment(minWords) << endl;
    }

    return 0;
}
