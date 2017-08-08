#ifndef TEXTREPRESENTATION_H
#define TEXTREPRESENTATION_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

typedef enum{
    ANALYSIS,
    TRAINING,
    TRAINING_SUM
} MessageType;

struct Word
{
    std::string word;
    int spamCount;
    int goodCount;
    float rSpam;
    float rGood;
    float pSpam;
    int exist = 0;
};

//Word NewWord(std::string word);

struct WordMap
{
    std::map<std::string, Word> words;
    long spamTotal = 0;
    long hamTotal = 0;
};

struct IntermediateAnalysisMessage
{
    std::string word;
    int count;
    int isSpam;
};

struct IntermediateTrainingMessage
{
    std::string word;
    int id;
    int numWords;
};

struct IntermediateTrainingSumMessage
{
    std::string placeHolderString;
    int spamCount;
    int hamCount;
};

struct AnalysisSummary
{
    std::vector<Word> words;
    int uniqueWords;
    int exist = 0;
};

Word NewWord(std::string word);
AnalysisSummary NewSummary();

/**
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
    as.exist = 1;
    return as;
};
**/
/**
float isWordInteresting(Word word){
    return std::abs(0.5f - word.pSpam);
};
**/
#endif
