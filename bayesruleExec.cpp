#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "textRepresentation.h"


Map<int, AnalysisSummary> summaries;

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
    }

    while(words_in_summary.size() > limit){
        words_in_summary.pop_back();
    }
}

// TODO: Convert this string into char buffer
void enclave_execute(std::string smessage) {

    IntermediateAnalysisMessage smessage = (IntermediateAnalysisMessage) smessage;
    std::string word = smessage.word;
    int id = smessage.id;
    int numWords = smessage.numWords;
    
    AnalysisSummary summary = summaries.at(id);

    if(summary == null){
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
