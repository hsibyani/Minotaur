#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"

//TODO: add tokenize
// TODO: Convert this string into char buffer
void enclave_execute(std::string smessage, Type type) {
    std::string content = smessage.content //TODO:
    if(type == TRAINING || type == TRAINING_SUM){
        bool isSpam = smessage.isSpam; //TODO: 

        Map<String, int> wordCounts = tokenize(content);
        int spamTotal = 0;
        int hamTotal = 0;

        std::map<std::string, int>::iterator it = wordCounts.begin();
        while(it != wordCounts.end()){
            std::string word = it->first;
            int count = it->second;

            if(isSpam){
                spamTotal += count;
            } 
            else{
                hamTotal += count;
            }

            //emit TRAINING
        }

        //emit TRAINING SUM
    } 
    else if(type == ANALYSIS){
        int id = smessage.id; //TODO:
        
        Map<String, int> wordCounts = tokenize(content);

        std::map<std::string, int>::iterator it = wordCounts.begin();
        while(it != wordCounts.end()){
            //emit ANALYSIS
        }
    }

}
