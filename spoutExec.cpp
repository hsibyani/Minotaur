/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "spoutExec.hpp"

int enclave_shuffle_routing(int j, int n){
    j++;
    j = j% n;
    return j;
}

// What needs to happen within the enclave?
void enclave_execute(int* j, int* n){
        *j = enclave_shuffle_routing(*j,*n);
        //return j;
}