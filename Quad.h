/*
 *  Quad.h
 *  FYP
 *
 *  Created by Paul Magrath on 17/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */
#ifndef QUAD_H
#define QUAD_H

#include <string>
#include <xmmintrin.h>
using namespace std;

struct Quad {
    union {
        __m128i data;
        float value[4];
        unsigned char c[16];
    };
    
public:
    Quad(){
        for (int i=0; i<=3;i++){
            value[i] = 0;
        }
    }
    
    Quad(int j){
        for (int i=0; i<=3;i++){
            value[i] = 0;
        }
        c[15] = j;
    }
    
    Quad(float v0, float v1, float v2, float v3){
        value[0] = v0;
        value[1] = v1;
        value[2] = v2;
        value[3] = v3;
    };
    
    Quad(__m128i d){
        data = d;
    };
    
    Quad(const unsigned char* s){
        for(int i=0; i<16; i++){
            c[i] = s[i];
        }
    }
    
    Quad(unsigned char* s){
        for(int i=0; i<16; i++){
            c[i] = s[i];
        }
    }
    
    Quad(const char* s){
        for(int i=0; i<16; i++){
            c[i] = s[i];
        }
    }
    
    Quad(string str){
        const char* s = str.c_str();
        for(int i=0; i<16; i++){
            c[i] = s[i];
        }
    }
    
    unsigned char* toArray(unsigned char* buf){
        for (int i=0; i<16; i++)
            buf[i] = c[i];
        return buf;
    }
    
    unsigned char* p(){
        return (unsigned char*) &c;
    }
    
    Quad increment(){
        c[15] += 1;
        if (c[15] == 0)
            c[14] += 1;
        return data;
    }
    
    Quad increment(int i){        
        for (int j=0; j<i;j++)
            increment();
        return data;
    }
};

#endif
