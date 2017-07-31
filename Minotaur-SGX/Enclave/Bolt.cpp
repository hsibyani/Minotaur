/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
using namespace std;

struct StringArray{
    char **array; 
};

class Bolt{
    
    public:
        virtual enclave_execute(string tuples, int numNextStage, StringArray** retTuples, int** tupleLengths, int *numTuples) = 0;

}
