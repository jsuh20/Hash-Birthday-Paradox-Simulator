#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Hashtable.h"
using namespace std;

#define protected public
#define private public
#undef protected
#undef private


string randString(int length){
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
    'r','s','t','u','v','w','x',
    'y','z'};
    string name = "";
    for (int i=0; i<length; i++){
        name = name + letters[rand()%26];
    }
    return name;
}

int main(){
    srand(time(0));
    int numProbes = 0;
    int twothreeorless = 0;
    for (int i=0; i<1000; i++){
        Hashtable<int> days(true, (unsigned int)365); 
        numProbes = 0;
        int timesInsert = 0;
        while (numProbes == 0){
            int length = rand()%28+1;
            string random = randString(length);
            numProbes = days.add(random, 11);
            timesInsert++;
        }
        if (timesInsert <= 23){
            twothreeorless++;
        }
    }
    double value = (double)twothreeorless/1000;
    cout << "value: " << value << endl;
}