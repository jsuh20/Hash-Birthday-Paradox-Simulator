#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstring>


//use pair to store k and val
//lookup --> find the T val
//resize --> in 'add' if load factor > 0.5
//dynamic array
template <class T>
class Hashtable{
    public:
        Hashtable(bool debug=false , unsigned int size=11);
        ~Hashtable();
        int add (std::string k, const T& val);
        const T& lookup (std::string k);
        void reportAll (std::ostream &) const;
        int hash (std::string k) const;
    private:
        void resize ();
        unsigned long int m; //size of hasht
        std::vector<std::pair<std::string, T>> hasht;
        bool debugVal;
        int numItems = 0;
        bool inHash(std::string k);
        unsigned long int rVal[5] = {983132572, 1468777056, 552714139, 984953261, 261934300};
        unsigned long int sizes[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
};

template <class T>
//hashtable constructor
Hashtable<T>::Hashtable(bool debug, unsigned int size){
    debugVal = debug;
    //for loop to round size to next largest number in size array
    for (int i=0; i<17; i++){
        if (size == sizes[i]){
            m = size;
            break;
        } else if (size < sizes[i]){
            m = sizes[i];
            break;
        }
    }
    //randomize r-vals if debug is off
    if (debugVal == false){
        for (int i=0; i<5; i++){
            rVal[i] = rand()%size+1;
        }
    }
    //initiaize hashtable as vector of pairs
    for (int i=0; i<m; i++){
        hasht.push_back(std::make_pair("key", 0));
    }
}

template <class T>
Hashtable<T>::~Hashtable(){
}


template <class T>
int Hashtable<T>::add(std::string k, const T & val){
    //resize if load factor greater than 0.5
    int numProbes = 0;
    double loadFactor = (double)numItems/m; 
    if (loadFactor >= 0.5){
        resize();
    }
    //quadratic probing and adding value
    if (!inHash(k)){
        numItems++;
        //get hash index
        int index = hash(k);
        //if value is 0, then means spot is empty
        if (hasht[index].second == 0){ 
            hasht[index].first = k;
            hasht[index].second = val;
        } else{
            //quadratic probing
            for (int i=0; i<m; i++){
                numProbes++;
                int newIndex = (int)(index + pow(i+1,2))%m;
                if (hasht[newIndex].second == 0){
                    hasht[newIndex].first = k;
                    hasht[newIndex].second = val;
                    break;
                }
            }
        }
        //find index using hash function
        //add value and key pair to hashtable at specified index
        //probe and increment numProbes as you go
    }
    return numProbes;
}

template <class T>
const T& Hashtable<T>::lookup (std::string k){
    if (!inHash(k)){
        unsigned long int index = hash(k);
        //if key of index1 is equal to input key, then set input key into that index
        if (hasht[index].first == k){
            return hasht[index].second;
        } else{
            //quadratic probing
            for (unsigned long int i=0; i<m; i++){
                unsigned long int newIndex = (int)(index + pow(i+1,2))%m;
                if (hasht[newIndex].first == k){
                    return hasht[newIndex].second; //change
                    break;
                }
            }
        }
    } else{
        return hasht[0].second;
    }
    return 0;
}

template <class T>
int Hashtable<T>::hash(std::string k) const{
    int intarrayindex = 4;
    //initialize array of w's with 0
    long long intArray[5] = {0,0,0,0,0};
    double twentysevenpowers[6] = {pow(27,0),pow(27,1),pow(27,2),pow(27,3),pow(27,4),pow(27,5)};
    //start from last character of word and operate on six of them
    for (int i = k.length()-1; i >= 0; i-=6){
        long long wVal = 0;
        for (int j=0; j<6; j++){
            if ((i-j) < 0){
                break;
            }
            int x = (int)k[i-j]-96;
            wVal += (x*twentysevenpowers[j]);
        }
         
        intArray[intarrayindex] = wVal;

        intarrayindex--;
    }
    //find sum
    long sum = 0;
    for (int i=0; i< 5; i++){
        sum += (long long)(rVal[i]*intArray[i]);
    }
    long index = sum % m;
    return index;
}

template <class T>
void Hashtable<T>::resize(){
    std::vector<std::pair<std::string,T>> currentones;
    for (int i=0; i<m; i++){
        if (hasht[i].second != 0){
            currentones.push_back(hasht[i]);
        }
    }
    hasht.resize((m * 2) + 1);   
    //rehash
    for (unsigned long int i=0; i<currentones.size(); i++){ 
        unsigned long int newpos = hash(currentones[i].first);
        hasht[newpos] = currentones[i]; 
    }
    //fill up new empty spots with 0 pair
    for (int i=0; i<m; i++){
        if (!hasht[i].second){
            hasht.push_back(std::make_pair("key", 0));
        }
    }
}

template <class T>
void Hashtable<T>::reportAll(std::ostream& ofile) const{
    for (int i=0; i<m; i++){
        if (hasht[i].second != 0){
            ofile << hasht[i].first << " " << hasht[i].second << std::endl;
        }
    }
}

//helper function to see if key is in hash table
template <class T>
bool Hashtable<T>::inHash(std::string k){
    for (int i=0; i<m; i++){
        if (k == hasht[i].first){
            return true;
        } else{
            return false;
        }
    }
    return 0; 
}


