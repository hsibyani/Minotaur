/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>
struct StringArray {
    char **array;
};

std::vector<std::string> splitTheInput(std::string str) {
    //MessageType (TRAINING = 0, ANALYSIS = 1)
    //SPAM (1 for spam, 0 for ham)
    //Message
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

void enclave_execute(std::string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc) {
    
    std::vector<std::string> args;
    args = splitTheInput(smessage);
    args.erase(args.begin());
    int type = std::stoi(args[0]);

    std::map<std::string, unsigned int> wordsCount;

    std::string word;
    std::istringstream iiss(args[2]);



    while(iiss>>word) {
        if (wordsCount.find(word) == wordsCount.end()) // Then we've encountered the word for a first time.
            wordsCount[word] = 1; // Initialize it to 1.
        else // Then we've already seen it before..
            wordsCount[word]++; // Just increment it.
    }

    if(type == 0) { //TRAINING
        int spamTotal = 0;
        int hamTotal = 0;

        bool isSpam = (bool) std::stoi(args[1]);
        
//        std::map<std::string, int>::iterator it = wordsCount.begin();
  //      while(it != wordsCount.end()){
//        for ( it; it != wordsCount.end(); it++ )
  //      {
        for(std::pair<std::string, int> element : wordsCount){
            if(isSpam) {
                spamTotal += element.second;
                std::cout << element.first << std::endl;
            } else {
                hamTotal += element.second;
            }
        }


        std::istringstream iss(args[2]);
        unsigned int j = 0;
        iss >> word;
        int count = std::distance(std::istream_iterator<std::string>(iss >> std::ws), std::istream_iterator<std::string>()) + 1;
        std::cout << "COUNT" << std::endl;
        std::cout << count << std::endl;
        *nc = count;
        *retmessage = (StringArray *) malloc(sizeof(StringArray));
        (*retmessage)->array = (char**) malloc(count * sizeof (char *));

        *retlen = (int *)malloc(count * sizeof (int));

        iss.clear();
        iss.seekg(0);


//    std::istringstream iss(smessage);

        iss >> word;
        int i = 0;
        while (iss >> word) {
            std::hash<std::string> hasher;
            auto hashed = hasher(word);
            j = hashed % n;
            *((*retlen)+i) = word.length() + std::to_string(j).length() + 2 + std::to_string(wordsCount[word]).length() + 1 + 2*std::to_string(1).length() + 2;
            (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
            snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %d %d %s %d", j, type, (int) isSpam, word.c_str(), wordsCount[word]);

            i = i+1;
        }
        std::cout << "sum0" << std::endl;
        *((*retlen)+i) = 2*std::to_string(0).length() + 2 + std::to_string(spamTotal).length() + 1 +std::to_string(hamTotal).length() + 1 + 1;
                std::cout << "sum1" << std::endl;

            (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
                    std::cout << "sum2" << std::endl;

            snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %d %d %d", 0, 2, spamTotal, hamTotal);
                    std::cout << "sum3" << std::endl;

    }

    else if(type == 1) {//ANALYSIS
        std::cout << "In analysis" << std::endl;
        std::string id = args[1];
        std::cout << id.length() << std::endl;

        std::istringstream iss(args[2]);
        iss >> word;
        int count = std::distance(std::istream_iterator<std::string>(iss >> std::ws), std::istream_iterator<std::string>());

        *nc = count;
        *retmessage = (StringArray *) malloc(sizeof(StringArray));
        (*retmessage)->array = (char**) malloc(count * sizeof (char *));

        *retlen = (int *)malloc(count * sizeof (int));

        iss.clear();
        iss.seekg(0);



        std::map<std::string, int>::iterator it;
        int wordCount;
        int i = 0;
        unsigned int j = 0;
        for(std::pair<std::string, int> element : wordsCount){
        //for ( it = wordsCount.begin(); it != wordsCount.end(); it++ )
        //{

            word = element.first;
            wordCount = element.second;

            std::hash<std::string> hasher;
            auto hashed = hasher(word);
            j = hashed % n;
            
            *((*retlen)+i) = word.length() + std::to_string(j).length() + 2 + 1 + 1 + std::to_string(type).length() + std::to_string(wordCount).length() + id.length() + 1;
            (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
            snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %d %s %s %d", j, type, id.c_str(), word.c_str(), wordCount);
            
            i = i+1;

        }

    }
}
