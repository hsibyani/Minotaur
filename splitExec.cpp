/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>

struct StringArray{
    char **array; 
};

void enclave_execute(std::string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc) {
    std::string word;
    std::istringstream iss(smessage);

    unsigned int j = 0;
    iss >> word;
    int count = std::distance(std::istream_iterator<std::string>(iss >> std::ws), std::istream_iterator<std::string>());

    *nc = count; 
    *retmessage = (StringArray *) malloc(sizeof(StringArray));
    (*retmessage)->array = (char**) malloc(count * sizeof (char *));

    *retlen = (int *)malloc(count * sizeof (int));
    
    iss.clear();
    iss.seekg(0);
    
    iss >> word;
    int i = 0;
    while (iss >> word) {
        std::hash<std::string> hasher;
        auto hashed = hasher(word);
        j = hashed % n;

        *((*retlen)+i) = word.length() + std::to_string(j).length() + 2;
        (*retmessage)->array[i] = (char *) malloc(*((*retlen)+i) * sizeof(char));
        snprintf((*retmessage)->array[i], *((*retlen)+i), "%d %s", j, word.c_str());

        i = i+1;
    }
}
