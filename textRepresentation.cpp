#include "textRepresentation.h"

AnalysisSummary NewSummary(){
    AnalysisSummary as;
    as.uniqueWords = 0;
    as.exist = 1;
    return as;
};

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
