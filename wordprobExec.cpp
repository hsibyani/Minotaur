#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"

WordMap wordMap;

// TODO: Convert this string into char buffer
void enclave_execute(AnalysisMessage smessage, Type type) {
    std::map<std::string, Word> words = wordMap.words;

    if(type == ANALYSIS){
        IntermediateAnalysisMessage smessage = (IntermediateAnalysisMessage) smessage;
        std::string word = smessage.word;
        int id = smessage.id;
        int numWords = smessage.numWords;

        Word w = words[word];

        if(w==NULL){
            w = NewWord(word);
            w.pSpam = 0.4f;
            words[word] = w;
        }
    
        if(isSpam){
            w.spamCount += count;
        } else {
            w.goodCount += count;
        }
        
    }else if(type == TRAINING){
        IntermediateTrainingMessage smessage = (IntermediateTrainingMessage) smessage;
        std::string word = smessage.word;
        int count = smessage.count;
        bool isSpam = (bool) smessage.isSpam;

        Word w = words[word];

        if(w==NULL){
            w = NewWord(word);
            words[word] = w;
        }

        if(spam){
            w.spamCount += count;
        } else {
            w.goodCount += count;
        }

    }else if(type == TRAINING_SUM){
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

}
