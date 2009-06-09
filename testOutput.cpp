/*
 *  testOutput.cpp
 *  FYP
 *
 *  Created by Paul Magrath on 30/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#include "testOutput.h"
#include "aes.h"
#include <iostream>

#define EXIT_SUCCESS 0

int main( int argc, char *argv[] ) {
    
    //std::cout << "ECB:\n";
    //aesDemo(ECB, "hello.txt",0);
    
    //std::cout << "\nCTR:\n";
	//aesDemo(CTR, "hello.txt",1);
    aesDemo(CTR, "H. G. Wells - War of the Worlds.txt",0);
    
    return EXIT_SUCCESS;
}
