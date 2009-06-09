/*
 *  core.cpp
 *  FYP
 *
 *  Created by Paul Magrath on 10/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include "core.h"
#include "utils.h"

using namespace std;



std::vector<std::string> prefetchToRegister(std::vector<std::string>& in,
                                         const int howFarAhead, const int howFarDown){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;
    
    string oldRef;
    if (howFarAhead !=0)
        oldRef = "source[i+"+itoa(howFarAhead)+"]";
    else
        oldRef = "source[i]";
    const string newVar = "src"+itoa(howFarAhead);
    
    int c = 0;
    
    while ((*i).find("// end unrolled loop")==string::npos){
        s = *i++;
        if (s.find("#define")==string::npos && s.find("encrypt_round")!=string::npos){
            c++;
            if (c == howFarDown) {
                out.push_back("        const vector_type "+newVar+" = "+oldRef+";\n");
            }
        }
        
        if (s.find("vector_type "+newVar)!=string::npos){
            // remove any other definition of same variable
        } else if (c >= howFarDown){
            out.push_back(replaceAll(s, oldRef, newVar));
        } else {
            out.push_back(s);
        }
    }
    
    while (i != in.end())
        out.push_back(*i++);
    
    return out;
}

std::vector<std::string> prefetchToCache(std::vector<std::string>& in,
                                            const int howFarAhead, const int howFarDown){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;
    int c = 0;
    
    while (i != in.end()){
        s = *i++;
        if (s.find("#define")==string::npos && s.find("encrypt_round")!=string::npos){
            c++;
            if (c == howFarDown) {
                out.push_back("        _mm_prefetch((char const*)&source[i+"+itoa(howFarAhead)+"],_MM_HINT_T0);\n");
            }
        }
        out.push_back(s);
    }
    
    return out;
}

std::vector<std::string> setLatencyTo(std::vector<std::string>& in,
                                      const int latency){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;
    
    while (i != in.end()){
        s = *i++;
        if (s.find("#define LATENCY ")!=string::npos){
            s = "#define LATENCY "+itoa(latency);
        }
        out.push_back(s);
    }
    return out;
}

std::vector<std::string> commentOpenMP(std::vector<std::string>& in){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;
    
    while (i != in.end()){
        s = *i++;
        if (s.find("#pragma omp")!=string::npos){
            s = replaceAll(s,"#pragma omp","// #pragma omp");
        }
        out.push_back(s);
    }
    return out;
}

std::vector<std::string> interleave(std::vector<std::string>& in,
                                    const int interleaveLevel){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;

    // open function
    while ((*i).find("vector_type result")==string::npos){
        out.push_back(*i++);
    }

    // interleave outer loop
    while ((*i).find("// end of original outer loop")==string::npos){
        if ((*i).find("result")!=string::npos || (*i).find("src")!=string::npos){
            for (int j=0; j<interleaveLevel; j++){
                s = replaceAll((*i),"result","result"+itoa(j));  
                s = replaceAll(s,"src","src"+itoa(j));  
                if (j!=0){
                    s = replaceAll(s,"_mm_set_epi32(0,0,0,i","_mm_set_epi32(0,0,0,i+"+itoa(j));
                    s = replaceAll(s,"source[i","source[i+"+itoa(j));
                    s = replaceAll(s,"dest[i","dest[i+"+itoa(j));
                }
                out.push_back(s);
                 
            }
        }
        else
            out.push_back(*i);
        i++;
    }

    // ignore further unrolls of outer loop so as to avoid duplication
    while ((*i).find("// end unrolled loop")==string::npos){
        i++;
    }

    // close function
    while (i != in.end()){
        s = *i++;
        if (s.find("result")!=string::npos || s.find("src")!=string::npos){
            s = replaceAll(s,"result","result0");
            s = replaceAll(s,"src","src0");
        }
        out.push_back(s);
    }

    return out;
}

std::vector<std::string> unwindOuterLoop(
                                         std::vector<std::string>& in, 
                                         const int unwindExtent){
    vector<string> out;
    vector<string> outerLoop;
    vector<string>::iterator inItr = in.begin();
    vector<string>::iterator outerLoopItr;
    string ompPragma = "";
    // open function
    while ((*inItr).find("i < limit")==string::npos){
        if ((*inItr).find("#pragma omp parallel for")==string::npos)
            out.push_back(*inItr++);
        else
            ompPragma = *inItr++;
    }
    // read in outer loop
    while ((*inItr).find("} // end outer loop")==string::npos){
        outerLoop.push_back(*inItr++);
    }
    // do unrolled iterations
    out.push_back("\n");
    out.push_back(ompPragma);
    out.push_back("\t for ( i = 0; i < (limit-"+ itoa(unwindExtent) +"); i+="+itoa(unwindExtent)+") {\n");
    out.push_back("\t   vector_type result;\n");
    out.push_back("\t   vector_type src;\n");        
    for (int j=0; j<unwindExtent; j++){
        for ( outerLoopItr = outerLoop.begin()+1; outerLoopItr+1 != outerLoop.end(); ++outerLoopItr ){
            *outerLoopItr = replaceAll(*outerLoopItr,"vector_type result;","");
            *outerLoopItr = replaceAll(*outerLoopItr,"const vector_type src =","src =");
            out.push_back(*outerLoopItr);
        }
        if (j==0)
            out.push_back(*outerLoopItr);          
        else
            out.push_back(replaceAll(*outerLoopItr,"dest[i]","dest[i+"+itoa(j)+"]"));
        out.push_back("\t\t  // end of original outer loop\n\n");
    }
    out.push_back("\t } // end unrolled loop\n");
    out.push_back("\n");    
    // finish off iterations
    out.push_back("\t while ( i < limit ) {\n");
    out.push_back("\t   vector_type result;\n");
    out.push_back("\t   vector_type src;\n");        
    for ( outerLoopItr = outerLoop.begin()+1; outerLoopItr+1 != outerLoop.end(); ++outerLoopItr ){
        out.push_back(*outerLoopItr);
    }
    out.push_back(replaceAll(*outerLoopItr,"[i]","[i++]"));

    // close function
    while (inItr != in.end()){
        out.push_back(*inItr);        
        ++inItr;
    }
    return out;
}

vector<string> useLocalVariables(
                                 vector<string>& in, 
                                 const int nKeys           ){
    vector<string> out;
    int i=0, j=0;
    string s;
    vector<string>::iterator itr;
    for ( itr = in.begin(); itr != in.end(); ++itr ){
        s = (*itr);
        if (s.find("int i;")!=string::npos){
            out.push_back(s);
            out.push_back("\n");
            while (j < nKeys){
                stringstream ss;
                ss << "\t const vector_type key" << j << " = keys[" << j << "];" << endl;
                out.push_back(ss.str());
                j++;
            }
            j=1;
            out.push_back("\n");
        } else if (j < nKeys 
                   && (*itr).find("encrypt_round")!=string::npos 
                   && (*itr).find("*(keys+"+itoa(j))!=string::npos) {
            out.push_back(replaceAll(s, "*(keys+", "(key"));
            j++;
        } else if (nKeys!=0 && (*itr).find("encrypt_final")!=string::npos){
            out.push_back(replaceAll(s, "*keys", "key0"));
        } else {
            out.push_back(s);
        }
        i++;
    }
    return out;
}

vector<string> unwindInnerLoop(
                          vector<string>& in, 
                          const int nKeys           )
{
    vector<string> out;
    int j=1;
    string s;
    vector<string>::iterator itr;
    for ( itr = in.begin(); itr != in.end(); ++itr ){
        if ((*itr).find("for (int j = 1; j < ")!=string::npos){
            s = replaceAll(*(++itr),"    result","result");
            while (j < nKeys){
                out.push_back(replaceAll(s,"j",itoa(j++)));
            }
            ++itr;
        }
        else 
            out.push_back(*itr);
    }
    return out;
}

std::vector<std::string> streamingStore(std::vector<std::string>& in){
    vector<string> out;
    vector<string>::iterator i = in.begin();
    string s;
    
    while (i != in.end()){
        s = *i++;
        if (s.find("dest[i] = result;")!=string::npos){
            out.push_back("\t   vector_store(&(dest[i]),result);\n");
        }
        else
            out.push_back(s);
    }
    return out;
}
