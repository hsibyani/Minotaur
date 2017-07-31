/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
using namespace std;

struct StringArray{
    string ** array;
}
// TODO: Convert this string into char buffer
void count_enclave_execute(string smessage);

void split_enclave_execute(string smessage, int n, void *sender, StringArray** retmessage, int ** retlen, int * nc);


// What needs to happen within the enclave?
void spout_enclave_execute(int* j, int* n);