/*
 *  utils.cpp
 *  FYP
 *
 *  Created by Paul Magrath on 09/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#include "utils.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using std::vector;
using namespace std;

void printArray(const vector<string> out){
    vector<string>::const_iterator itr;
    int i = 0;
    for ( itr = out.begin(); itr != out.end(); ++itr ){
        if (i<10)
            cout << "00";
        else if (i<100)
            cout << "0";
        cout <<  i++ << " " << *itr;
    }
} /* printArray */

void writeArrayToFile(string filename, const vector<string> out){
    writeArrayToFile(filename.c_str(),out);
} /* writeArrayToFile */

void writeArrayToFile(const char* filename, const vector<string> out){
    ofstream fout(filename, ios::trunc);
    vector<string>::const_iterator itr;
    
    for ( itr = out.begin(); itr != out.end(); ++itr ){
        fout << *itr;
    }
    
    cout << "Finished writing: " << filename << endl;
} /* writeArrayToFile */

string replaceAll(const string& str, const string& substring, const string& replacement){
    string s = str;
    int pos = s.find(substring,0);
    while (pos != -1) {
        s.replace(pos, substring.length(), replacement);
        pos = s.find(substring,pos+replacement.length());
    }
         
    return s;
} /* replaceAll */

string readFile(const char* filename){
    string line;
    string input;
    ifstream in(filename);
    
    while(getline(in,line))
        input += line;
    
    return input;
} /* readFile */

vector<string> readFileToArray(const char* filename){
    string line;
    vector<string> input;
    input.clear();
    ifstream in(filename, std::ios_base::in);
    
    if (!in.good()){
        cerr << "Unable to find input file: " << filename << endl;
        exit(-1);
    }
    
    while(getline(in, line, '\n')){
        input.push_back(line + "\n");
    }
    
    return input;
} /* readFileToArray */

string itoa(const int i){
    std::stringstream out;
    out << i;
    return out.str();
} /* itoa */

string itoa2(const int i){
    std::stringstream out;
    if (i<10)
        out << 0;
    out << i;
    return out.str();
} /* itoa */

int getPropertyValue(const string argv){
    if (argv.length()==0)
        return 0;
    return atoi(string(argv).substr(string(argv).find("=")+1).c_str());
}
