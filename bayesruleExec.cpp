#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"

std::map<std::string, AnalysisSummary> summaries;

struct StringArray {
    char **array;
};

float isWordInteresting(Word word) {
    return std::abs(0.5f - word.pSpam);
}

std::vector<std::string> splitTheInput_br(std::string str) {
    //MessageType (TRAINING = 0, ANALYSIS = 1)
    //ID
    //Message
    //wordCount
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
        if(argnum == 10) {
            args.push_back(str.substr(start, strSize - start +1));
            break;
        }
    }
    return args;
}


//Bayes Rule
//
float bayes(AnalysisSummary &analysis_summary) {
    float pposproduct = 1.0f;
    float pnegproduct = 1.0f;
    //std::cout << "IN BAYES" << std::endl;
    //std::cout << analysis_summary.words.size() << std::endl;
//    std::vector<Word> words_in_summary = analysis_summary.words;
    Word w;
    for(int i=0; i<analysis_summary.words.size(); i++) {
        w = analysis_summary.words.at(i);
        //std::cout << "BAYES INFO" << std::endl;
        //std::cout << w.pSpam << std::endl;
        pposproduct *= w.pSpam;
        pnegproduct *= (1.0f - w.pSpam);
    }

    return pposproduct / (pposproduct + pnegproduct);
}

void updateSummary(AnalysisSummary &analysis_summary, Word word) {
    int limit = 10;

    if(analysis_summary.words.size()==0) {
        analysis_summary.words.push_back(word);
    }
    else {

        for(int i=0; i<analysis_summary.words.size(); i++) {
            Word w = analysis_summary.words.at(i);
            if(word.word == w.word) {
                break;
            }
            else if(isWordInteresting(word) > isWordInteresting(w)) {
                analysis_summary.words.insert(analysis_summary.words.begin()+i, word);
                break;
            }
            else if(i == analysis_summary.words.size() - 1) {
                analysis_summary.words.push_back(word);
            }
        }
        while(analysis_summary.words.size() > limit) {
            analysis_summary.words.pop_back();
        }

    }
    //MOVE WHILE FROM HERE
}

// TODO: Convert this string into char buffer
void enclave_execute_br(std::string smessage, int n, StringArray** retmessage, int ** retlen, int * nc) {

    std::vector<std::string> args;
    args = splitTheInput_br(smessage);
    args.erase(args.begin());
    int type = std::stoi(args[0]);

    std::string mes = args[2];

    Word word = NewWord(mes);
    word.spamCount = std::stoi(args[3]);
    word.goodCount = std::stoi(args[4]);

    word.rSpam = std::stof(args[5]);
    word.rGood = std::stof(args[6]);
    word.pSpam = std::stof(args[7]);
    word.exist = std::stoi(args[8]);

    std::string id = args[1];
    //std::cout << args[3] << std::endl;
    int numWords = std::stoi(args[9]);

    AnalysisSummary summary = summaries[id];

    if(summary.exist == 0) {
        summary = NewSummary();
        summaries[id] = summary;
    } else {
        //std::cout << "ID EXISTS" << std::endl;
    }

    summary.uniqueWords += 1;

    updateSummary(summary, word);
    float spamProbability = 0.5;
    if(summary.uniqueWords >= numWords) {
        float pspam = bayes(summary);
        //TODO: emit value
        if(pspam > spamProbability) {
            //std::cout << "SPAM" << std::endl;
        }
        else {
            //std::cout << "NOT SPAM" << std::endl;
        }
        //std::cout << pspam << std::endl;
        summaries.erase(id);
    }
}

