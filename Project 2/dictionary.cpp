#include "dictionary.h"

Dictionary::Dictionary(){
    // Task 1.1: Implement the constructor of Dictionary.
    arraySize = 0;
    dataPairs = nullptr;
}

Dictionary::~Dictionary(){
    // Task 1.2: Implement the destructor of Dictionary.
    if (dataPairs != nullptr)
    {
        //cout << "Dictionary byebye" << endl;
        delete [] dataPairs;
        dataPairs = nullptr;
    }
}

int Dictionary::find(const string &key) const{
    // Task 1.3: Search a given key from the Dictionary.
    if (arraySize == 0)
        return NULL_VALUE;
    else
    {
        for (int i = 0; i < arraySize; i++)
        {
            if (dataPairs[i].key == key)
                return dataPairs[i].value;
        }
    }
    return NULL_VALUE;
}

bool Dictionary::insert(const string &key, int value){
    // Task 1.4: Insert a given pair into the Dictionary.
    if (find(key) == NULL_VALUE)  //exist
    {
        DataPair* newarr = new DataPair[arraySize + 1];
        for (int i = 0; i < arraySize; i++)
        {
            newarr[i] = dataPairs[i];
        }
        if (dataPairs != nullptr)
            delete [] dataPairs;

        newarr[arraySize].key = key;
        newarr[arraySize].value = value;
        arraySize++;
        dataPairs = newarr;
    }
    else
        return false;
    
    return true;
}