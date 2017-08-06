/**
#include <iostream>
#include <string>
#include "textRepresentation.h"

Word NewWord(std::string word){
    Word w;
    w.word = word;
    w.spamCount = 0;
    w.goodCount = 0;
    w.rSpam = 0.0f;
    w.rGood = 0.0f;
    w.pSpam = 0.0f;
    w.exist = 1;
    return w;
};

AnalysisSummary NewSummary(){
    AnalysisSummary as;
    as.uniqueWords = 0;
    return as;
};

float isWordInteresting(Word word){
    return abs(0.5f - word.pSpam);
};

**/
