/*
 *  main.cpp
 *  FYP
 *
 *  Created by Paul Magrath on 09/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include "aes.h"
#include "core.h"
#include "utils.h"

#define nKeys 14
#define EXIT_SUCCESS 0

using std::vector;
using namespace std;

bool ss = false;
bool ui = false;
bool local = false;
bool unroll = false;
bool leave = false;
bool prefetchCache = false;
bool prefetchRegister = false;
bool omp = false;

int jmin=0, jmax=nKeys,kmin=2,kmax=nKeys;

void processArguments( int argc, char *argv[] );
void generateVariants(const aes_mode,const int);

int main( int argc, char *argv[] ) {
    processArguments(argc,argv);
    generateVariants(CTR,5);
    return EXIT_SUCCESS;
}

void generatePrefetchRegisterVariants(std::vector<std::string> in, std::string baseFilename, int i){
    for (int m=1; m<10; m++){
        string file = replaceAll(baseFilename, ".cpp", "-RegisterDistance"+itoa(m)+".cpp");
        std::vector<std::string> out;
        for (int j=0; j<10; j++){
            string filename = replaceAll(file, ".cpp", "-RegisterSource"+itoa(j)+".cpp");
            out = prefetchToRegister(in,j,m*14);
            writeArrayToFile(filename,out);
        }
    }
}

void generatePrefetchCacheVariants(std::vector<std::string> in, std::string baseFilename, int i){
    for (int m=1; m<10; m++){
        string file = replaceAll(baseFilename, ".cpp", "-CacheDistance"+itoa(m)+".cpp");
        std::vector<std::string> out;
        for (int j=0; j<10; j++){
            string filename = replaceAll(file, ".cpp", "-CacheSource"+itoa(j)+".cpp");
            out = prefetchToCache(in,j,m*14); 
            writeArrayToFile(filename,out);
        }
    }
}

void generateInterleavedVariants(std::vector<std::string> in, std::string filename, int i){
    
    std::vector<std::string> out = interleave(in, i);
    writeArrayToFile(filename,out);
    
    if (prefetchCache)    
        generatePrefetchCacheVariants(out, replaceAll(filename, ".cpp", "-Prefetch.cpp"), i);
    if (prefetchRegister)
        generatePrefetchRegisterVariants(out, replaceAll(filename, ".cpp", "-Prefetch.cpp"), i);
}

void generateUnwoundOuterLoopVariants(std::vector<std::string> in, std::string filename, int i){
    
    std::vector<std::string> out = unwindOuterLoop(in, i);
    
    if (unroll){
        writeArrayToFile(filename,out);
        
        if (prefetchCache)
            generatePrefetchCacheVariants(out, replaceAll(filename, ".cpp", "-Prefetch.cpp"), i);
        if (prefetchRegister)
            generatePrefetchRegisterVariants(out, replaceAll(filename, ".cpp", "-Prefetch.cpp"), i);
    }
    
    if (leave)
        generateInterleavedVariants(out, replaceAll(filename, "Unwound", "Interleaved"), i);
}

void generateLocalVariableVariants(std::vector<std::string> in, std::string baseFilename){
    for (int j=jmin; j<=jmax; j++){
        std::vector<std::string> out = useLocalVariables(in, j);
        string filename = replaceAll(baseFilename, ".cpp","-"+itoa2(j)+"LocalVariables.cpp");
        writeArrayToFile(filename,out);
        
        if (unroll | leave)
            for (int k=kmin; k<=kmax; k++){
                generateUnwoundOuterLoopVariants(out,  replaceAll(filename, ".cpp", "-Unwound"+itoa2(k)+".cpp"), k);
            }
    }
}

void generateUnwoundInnerLoopVariants(std::vector<std::string> in, std::string filename){
    
    std::vector<std::string> out = unwindInnerLoop(in, nKeys);
    filename = replaceAll(filename.c_str(), ".cpp","-UI.cpp");
    
    if (local)
        generateLocalVariableVariants(out,filename);
    else if (unroll | leave)
        for (int k=kmin; k<=kmax; k++){
            generateUnwoundOuterLoopVariants(out,  replaceAll(filename, ".cpp", "-Unwound"+itoa2(k)+".cpp"), k);
        }
    else
        writeArrayToFile(filename,out);
}

void generateStreamingStoreVariants(std::vector<std::string> in, std::string filename){
    vector<string> out = streamingStore(in);
    string outputFilename = replaceAll(filename, ".cpp","-S.cpp");
    writeArrayToFile(outputFilename.c_str(),out);
    
    if (ui)
        generateUnwoundInnerLoopVariants(out,outputFilename);
}

void generateOpenMPVariants(std::vector<std::string> in, std::string filename){
    vector<string> out = in;
    string outputFilename = replaceAll(filename, "output-", "output-omp-");
    writeArrayToFile(outputFilename.c_str(),out);
    
    if (ui)
        generateUnwoundInnerLoopVariants(out,outputFilename);
    
    if (ss)
        generateStreamingStoreVariants(out, outputFilename);
}

void processArguments(int argc, char *argv[]){
    if (argc == 1){
        cout << "Usage: " << argv[0] <<" [+ss] [+ui] [+local[=X]] [+unroll] [+leave[=X]] [+prefetchCache] [+prefetchRegister] [+omp]\n";
        exit(0);
    }
    
    for (int i=0; i<argc; i++){
        if (string(argv[i]).find("+ss")!=string::npos) {
            ss = true;
        } else if (string(argv[i]).find("+ui")!=string::npos) {
            ui = true;
        } else if (string(argv[i]).find("+local")!=string::npos) {
            ui = true;
            local = true;        
            if (string(argv[i]).find("=")!=string::npos)
                jmin = jmax = getPropertyValue(argv[i]);
        } else if (string(argv[i]).find("+unroll")!=string::npos) {
            unroll = true;
            if (string(argv[i]).find("=")!=string::npos) {
                kmin = kmax = getPropertyValue(argv[i]);
                if (kmin < 2) cerr << "Invalid argument.\n", exit(-1);
            }
        } else if (string(argv[i]).find("+leave")!=string::npos) {
            leave = true;
            if (string(argv[i]).find("=")!=string::npos){
                kmin = kmax = getPropertyValue(argv[i]);
                if (kmin < 2) cerr << "Invalid argument.\n", exit(-1);
            }
        } else if (string(argv[i]).find("+prefetchCache")!=string::npos) {
            prefetchCache = true;
        } else if (string(argv[i]).find("+prefetchRegister")!=string::npos) {
            prefetchRegister = true;
        } else if (string(argv[i]).find("+omp")!=string::npos) {
            omp = true;
        } else if (string(argv[i]).find("+aesDemo")!=string::npos) {
            aesDemo(CTR, "../../hello.txt",1);
        }
    }
}

void generateVariants(const aes_mode mode, const int latency){
    std::vector<std::string> in;
    std::vector<std::string> out;
    std::string inputFilename;
    std::string outputFilename;
    
    if (mode == CTR)        inputFilename = "input-ctr.cpp";
    else                    inputFilename = "input-ecb.cpp";
    outputFilename = replaceAll(inputFilename, "input","output");
    
    out = setLatencyTo(in = readFileToArray(inputFilename.c_str()),latency);
    outputFilename = replaceAll(outputFilename, ".cpp","-L"+itoa(latency)+".cpp");
    writeArrayToFile(outputFilename.c_str(),commentOpenMP(out));
    
    if (ui)
        generateUnwoundInnerLoopVariants(commentOpenMP(out),outputFilename);
    
    if (ss)
        generateStreamingStoreVariants(commentOpenMP(out), outputFilename);
    
    if (omp)
        generateOpenMPVariants(out, outputFilename);
}
