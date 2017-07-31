/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Enclave.hpp"

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>

std::map<std::string, int> count_map;

// TODO: Convert this string into char buffer
void count_enclave_execute(std::string smessage) {

    std::string word;
    std::istringstream iss(smessage);
    iss >> word;
    //std::cout << word << std::endl;
    iss >> word;
    //std::cout << word << std::endl;
    if (count_map.find(word) != count_map.end()) {
        count_map[word] += 1;
    } else {
        count_map[word] = 1;
    }
    std::map<std::string, int > ::iterator it;
    // Printing the counts
    for (it = count_map.begin(); it != count_map.end(); it++) {
        std::cout << it->first // string (key)
                << ':'
                << it->second // string's value 
                << std::endl;
    }
}

void split_enclave_execute(std::string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc) {
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

int enclave_shuffle_routing(int j, int n){
    j++;
    j = j% n;
    return j;
}

// What needs to happen within the enclave?
void spout_enclave_execute(int* j, int* n){
        *j = enclave_shuffle_routing(*j,*n);
        //return j;
}