#include <string>
#include <map>
#include <sstream>
#include <iostream>

std::map<std::string, int> count_map;

// TODO: Convert this string into char buffer
void enclave_execute(std::string smessage) {

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