/*
 *  core.h
 *  FYP
 *
 *  Created by Paul Magrath on 10/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#include <string>
#include <vector>

std::vector<std::string> streamingStore(std::vector<std::string>& in);

std::vector<std::string> unwindInnerLoop(
                                      std::vector<std::string>& in, 
                                      const int nKeys           );

std::vector<std::string> useLocalVariables(
                                           std::vector<std::string>& in, 
                                           const int nKeys           );

std::vector<std::string> unwindOuterLoop(
                                         std::vector<std::string>& in, 
                                         const int unwindExtent);

std::vector<std::string> interleave(std::vector<std::string>& in,
                                    const int interleaveLevel);

std::vector<std::string> commentOpenMP(std::vector<std::string>& in);

std::vector<std::string> setLatencyTo(std::vector<std::string>& in,
                                    const int latency);

std::vector<std::string> prefetchToCache(std::vector<std::string>& in,
                                      const int, const int);

std::vector<std::string> prefetchToRegister(std::vector<std::string>& in,
                                         const int, const int);
