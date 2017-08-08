#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"
#include <vector>
#include <iterator>

WordMap wordMap;
Word NewWord(std::string word);
std::map<std::string, Word> words = wordMap.words;

struct StringArray {
    char **array;
};

std::vector<std::string> splitTheInput_wp(std::string str) {
    //MessageType (TRAINING =0, ANALYSIS = 1)
    //SPAM NOT SPAM
    //COUNT
    //WORD
    std::vector<std::string> args;
    int argnum = 0;
    int strSize = str.length();
    int start = 0;
    for (int i = 0; i<str.length(); i++) {
        if(str[i]==' ') {
            args.push_back(str.substr(start, i-start));
            start = i+1;
            argnum++;
        }
        if(argnum == 4) {
            args.push_back(str.substr(start, strSize - start +1));
            break;
        }
    }
    return args;
}

std::vector<std::string> splitTheInput_wp_ts(std::string str) {
    //MessageType (TRAINING =0, ANALYSIS = 1)
    //SPAM NOT SPAM
    //COUNT
    //WORD
    std::vector<std::string> args;
    int argnum = 0;
    int strSize = str.length();
    int start = 0;
    for (int i = 0; i<str.length(); i++) {
        if(str[i]==' ') {
            args.push_back(str.substr(start, i-start));
            start = i+1;
            argnum++;
        }
        if(argnum == 3) {
            args.push_back(str.substr(start, strSize - start +1));
            break;
        }
    }
    return args;
}



// TODO: Convert this string into char buffer
void enclave_execute_wp(std::string smessage, int n, StringArray** retmessage, int ** retlen, int * nc) {

//    std::map<std::string, Word> words = wordMap.words;
    std::cout << smessage << std::endl;
    std::vector<std::string> args;
    args = splitTheInput_wp(smessage);
    args.erase(args.begin());

    int type = std::stoi(args[0]);

    std::istringstream iss(args[2]);
    unsigned int j = 0;


    std::string word;
    iss >> word;
    int count = std::distance(std::istream_iterator<std::string>(iss >> std::ws), std::istream_iterator<std::string>());

    *nc = count;
    *retmessage = (StringArray *) malloc(sizeof(StringArray));
    (*retmessage)->array = (char**) malloc(count * sizeof (char *));

    *retlen = (int *)malloc(count * sizeof (int));

    iss.clear();
    iss.seekg(0);


    if(type == 1) { //ANALYSIS
        std::cout << "analysis" << std::endl;
        std::string word = args[2];
        int wordCount = std::stoi(args[3]);
        std::string id = args[1];

        Word w = words[word];

        if(w.exist == 0) {
            w = NewWord(word);
            w.pSpam = 0.4f;
            words[word] = w;
        }

        std::map<std::string, int>::iterator it;
        int i = 0;
        unsigned int j = 0;

        std::hash<std::string> hasher;
        auto hashed = hasher(word);
        j = hashed % n;

        *((*retlen)+i) = word.length() + std::to_string(j).length() + 2 + 1 + 1 + std::to_string(type).length() + std::to_string(wordCount).length() + id.length() + 1;
        (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
        snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %d %s %s %d", j, type, id.c_str(), word.c_str(), wordCount);

        std::cout << (*retmessage)->array[i] << std::endl;
        i = i+1;


    } else if(type == 0) {//TRAINING
        std::string word = args[2];
        int count = std::stoi(args[3]);
        bool isSpam = (bool) std::stoi(args[1]);

        Word w = words[word];

        if(w.exist==0) {
            w = NewWord(word);
            words[word] = w;
        }

        if(isSpam) {
            w.spamCount += count;
        } else {
            w.goodCount += count;
        }
    }
    else if(type == 2){
        args = splitTheInput_wp_ts(smessage);
        std::cout << "in type 2" << std::endl;
        std::cout << args[2] << std::endl;
                std::cout << args[1] << std::endl;
        int hamCount = std::stoi(args[2]);
        int spamCount = std::stoi(args[1]);

        wordMap.spamTotal += spamCount;
        wordMap.hamTotal += hamCount;

        std::map<std::string, Word>::iterator it;
        for(std::pair<std::string, Word> element : words){

            Word tmpWord = element.second;

            int spamTotal = wordMap.spamTotal;
            int hamTotal = wordMap.hamTotal;

            if(spamTotal > 0){
                tmpWord.rSpam = tmpWord.spamCount / (float) spamTotal;
            }
            if(hamTotal > 0){
                tmpWord.rGood = 2*tmpWord.goodCount / (float) hamTotal;
            }

            if(tmpWord.rGood + tmpWord.rSpam > 0){
                tmpWord.pSpam = tmpWord.rSpam / (tmpWord.rSpam + tmpWord.rGood);
            }
            if(tmpWord.pSpam < 0.01f){
                tmpWord.pSpam = 0.01f;
            }else if(tmpWord.pSpam > 0.99f){
                tmpWord.pSpam = 0.99f;
            }
        }

    }
}
