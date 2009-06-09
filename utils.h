/*
 *  utils.h
 *  FYP
 *
 *  Created by Paul Magrath on 09/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#define DUMP(s, i, buf, sz)  {      \
    printf(s);                      \
    printf("\t");                   \
    for (i = 0; i < (sz);i++){      \
        printf("%02x ", buf[i]);    \
        if (i%16==15 && i+1< (sz))  \
            printf("\n         \t\t"); \
    }                               \
    printf("\n");                   \
}

#include <string>
#include <vector>
using namespace std;

void printArray(const vector<string> out);
void writeArrayToFile(string filename, const vector<string> out);
void writeArrayToFile(const char* filename, const vector<string> out);
string replaceAll(const string& str, const string& substring, const string& replacement);
string readFile(const char* filename);
vector<string> readFileToArray(const char* filename);
int getPropertyValue(const string argv);
string itoa(const int i);
string itoa2(const int i);
