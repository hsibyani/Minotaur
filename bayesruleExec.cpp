#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"

std::map<std::string, AnalysisSummary> summaries;

struct StringArray {
    char **array;
};

float isWordInteresting(Word word){
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
        if(argnum == 4) {
            args.push_back(str.substr(start, strSize - start +1));
            break;
        }
    }
    return args;
}


//Bayes Rule
//
float bayes(AnalysisSummary analysis_summary){
    float pposproduct = 1.0f;
    float pnegproduct = 1.0f;

    std::vector<Word> words_in_summary = analysis_summary.words;
    Word w;
    for(int i=0; i<words_in_summary.size(); i++){
        w = words_in_summary[i];
        pposproduct *= w.pSpam;
        pnegproduct *= (1.0f - w.pSpam);
    }

    return pposproduct / (pposproduct + pnegproduct);
}

void updateSummary(AnalysisSummary analysis_summary, Word word){
    int limit = 10;

    if(analysis_summary.uniqueWords == 0){
        analysis_summary.words.push_back(word);
    }
    else{
        std::vector<Word> words_in_summary = analysis_summary.words;

        for(int i=0; i<words_in_summary.size(); i++){
            Word w = words_in_summary.at(i);
            if(word.word == w.word){
                break;
            }
            else if(isWordInteresting(word) > isWordInteresting(w)){
                words_in_summary.insert(words_in_summary.begin()+i, word);
                break;
            }
            else if(i == words_in_summary.size() - 1){
                words_in_summary.push_back(word);
            }
        }
        while(words_in_summary.size() > limit){
        words_in_summary.pop_back();
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

    std::string id = args[1];
    std::cout << args[3] << std::endl;
    int numWords = std::stoi(args[3]);
    
    AnalysisSummary summary = summaries[id];

    if(summary.exist == 0){
        summary = NewSummary();
        summaries[id] = summary;
    }

    summary.uniqueWords += 1;

    updateSummary(summary, word);

    if(summary.uniqueWords >= numWords){
        float pspam = bayes(summary);
        //TODO: emit value
        summaries.erase(id);
    }
}

