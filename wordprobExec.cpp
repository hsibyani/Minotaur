#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"
#include <vector>

WordMap wordMap;
Word NewWord(std::string word);

struct StringArray{
    char **array;
};

std::vector<std::string> splitTheInput(std::string str){
    //MessageType (ANALYSIS...
    //SPAM NOT SPAM
    //COUNT
    //WORD
    std::vector<std::string> args;
    int argnum = 0;
    int strSize = str.length();
    int start = 0;
    for (int i = 0; i<str.length(); i++){
       if(str[i]==' '){
           args.push_back(str.substr(start, i-start+1));
           start = i+1;
           argnum++;
       }
       if(argnum == 3){
           args.push_back(str.substr(start, strSize - start +1));
           break;
       }
    }
    return args;
}


// TODO: Convert this string into char buffer
void enclave_execute_wp(std::string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc) {
    
    std::map<std::string, Word> words = wordMap.words;

    std::vector<std::string> args;
    args = splitTheInput(smessage);

    int type = std::stoi(args[0]);
/**
    if(type == 0){
        IntermediateAnalysisMessage smessage = (IntermediateAnalysisMessage) smessage;
        std::string word = smessage.word;
        int id = smessage.id;
        int numWords = smessage.numWords;

        Word *w = &words[word];

        if(w==NULL){
            w = NewWord(word);
            w.pSpam = 0.4f;
            words[word] = w;
        }
    
    }else 
    **/
    if(type == 1){
        std::string word = args[3];
        int count = std::stoi(args[2]);
        bool isSpam = (bool) std::stoi(args[1]);

        Word w = words[word];

        if(w.exist==0){
            w = NewWord(word);
            words[word] = w;
        }

        if(isSpam){
            w.spamCount += count;
        } else {
            w.goodCount += count;
        }

    }
    /**
    else if(type == 2){
        IntermediateTrainingSumMessage smessage = (IntermediateTrainingSumMessage) smessage;
        int spamCount = smessage.spamCount;
        int hamCount = smessage.hamCount;

        wordMap.spamTotal += spamCount;
        wordMap.hamTotal += hamCount;

        std::map<std::string, Word>::iterator it = words.begin();
        while(it != words.end()){
            Word tmpWord = it->second;

            tmpWord.spamTotal tmpWord.hamTotal;

            if(tmpWord.spamTotal > 0){
                tmpWord.rSpam = tmpWord.spamTotal / (float) tmpWord.spamTotal;
            }
            if(tmpWord.spamTotal > 0){
                tmpWord.rGood = 2*tmpWord.goodTotal / (float) tmpWord.spamTotal;
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
**/
}
