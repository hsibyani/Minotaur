#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
using namespace std;

typedef enum{
    ANALYSIS,
    TRAINING,
    TRAINING_SUM
} Type;

struct Word
{
    std::string word;
    int spamCount;
    int goodCount;
    float rSpam;
    float rGood;
    float pSpam;
};

Word NewWord(std::string word);

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
}

struct IntermediateTrainingMessage
{
    std::string word;
    int id;
    int numWords;
}

struct IntermediateTrainingSumMessage
{
    std::string placeHolderString;
    int spamCount;
    int hamCount;
}

struct AnalysisSummary
{
    std::vector<Word> words;
    int uniqueWords;
};

AnalysisSummary NewSummary();

#endif
