#ifndef COMMENTGENERATOR_HPP
#define COMMENTGENERATOR_HPP

#include <string>
#include <dirent.h> //opening directory
#include <stdlib.h> //random generator
#include <unordered_map>
#include <vector>
#include <cctype>
#include <fstream>  //input file
using namespace std;

class CommentGenerator{
public:

    // the constructor function takes the goodreviews.txt and badreviews.txt
    // from the dat directory, and record the data into two Markov's chain for
    // the praiser and critic
    CommentGenerator(const string filesLoc = "dat/" ) {

        // read the cleaned review file
        fstream infile, infile2;
        infile.open(filesLoc+"goodreviews.txt");
        infile2.open(filesLoc+"badreviews.txt");
        if (infile.fail() || infile2.fail()){
            cerr << "Wrong data directory" << endl;
            exit(-1);
        }
        string prevWord = ".";
        string line;
        while(getline(infile, line)) {
            vector<string> sentence;
            tokenize(sentence,line);
            if (sentence.size()){
                for (unsigned int i = 0; i < sentence.size(); i++){
                    praiser[prevWord].first++;
                    praiser[prevWord].second[sentence[i]]++;
                    prevWord = sentence[i];
                }
            }
        }
        infile.close();
        infile.clear();
        while(getline(infile2, line)) {
            vector<string> sentence;
            tokenize(sentence,line);
            if (sentence.size()){
                for (unsigned int i = 0; i < sentence.size(); i++){
                    critic[prevWord].first++;
                    critic[prevWord].second[sentence[i]]++;
                    prevWord = sentence[i];
                }
            }
        }
        infile2.close();
        infile2.clear();
        srand(time(0));

    }

    // randomly generate a music instrument comment
    // that has a length longer than minWords
    string comment(int minWords) {
        // randomly decide good or bad comment
        bool praise = false;
        if (rand() % 2) praise = true;

        string prevWord = getNextWord(".", praise);
        string response = "";
        
        // capitalize the fisrt word
        response += char(toupper(int(prevWord[0]))) + prevWord.substr(1,prevWord.length()-1);
        
        // generate the rest
        while (true){
            if (prevWord == "." && minWords <= 0)
                return response;
            prevWord = getNextWord(prevWord, praise);
            if (PUNCTUATION.find(prevWord) != string::npos)
                response += prevWord;
            else
                response += (" " + prevWord);
            --minWords;
        }
        return "";
    }

    // get the previous word and randomly generate a possible next word.
    // the bool variable prase indicate whether to use the good review data.
    string getNextWord(const string &prevWord, bool praise) {
        if (praise){
        int randPos = rand() % praiser[prevWord].first + 1;
        for(auto it = praiser[prevWord].second.begin(); it != praiser[prevWord].second.end(); ++it )
        {
            randPos -= it->second;
            if (randPos <= 0)
                return it->first;
        }
      }
      else{
        int randPos = rand() % critic[prevWord].first + 1;
        for(auto it = critic[prevWord].second.begin(); it != critic[prevWord].second.end(); ++it )
        {
            randPos -= it->second;
            if (randPos <= 0)
                return it->first;
        }
      }
        return "";
    }

    ~CommentGenerator() {
        praiser.clear(); critic.clear();
    }

    //Feel free to put your own code here

private:
    const string PUNCTUATION = ".!,?";
    const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
    const string whitespace = " \t\r\n\v\f";    //from AutocompleteUtils

    //a unordered map matches word to <number of next word,
    //a map that match the next word to it frequency that appears after nextword
    unordered_map<string,pair<unsigned short,unordered_map<string,unsigned short>>> praiser;
    unordered_map<string,pair<unsigned short,unordered_map<string,unsigned short>>> critic;

    // separate each word and important punctuations
    void tokenize(vector<string> &sentence, const string &line) {
        vector<char> word;
        for (unsigned char c : line) {

            // accept other characters
            if(UNWANTED_CHARACTERS.find(c) != string::npos) continue;

            // word divider
            if (whitespace.find(c) != string::npos) {
                if (word.size()) {
                    sentence.push_back(string(word.begin(), word.end()));
                    word.clear();
                }
            }
            // a punctuation
            else if (PUNCTUATION.find(c) != string::npos)
            {
                if (word.size()){
                    sentence.push_back(string(word.begin(), word.end()));//push the word part of "word."
                    word.clear();
                }
                // treat a punctuation as a word
                sentence.push_back(string(1, c));
            }
            else
                word.push_back(c);
        }
        // a line ended with a word, push the word
        if (word.size() > 0) sentence.push_back(string(word.begin(), word.end()));
    }
};


#endif //CommentGenerator_hpp
