#ifndef includes_h
#define includes_h
//*****************************************************||
//*************** Mainly used Includes *****************||
//*******************************************************||

//*****************||
//**!STD INCLUDES!**||
//*******************||

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

//*********************||
//***!BOOST INCLUDES!***||
//***********************||

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

//*************************||
//***!GLOBAL DEFINITIONS!***||
//***************************||

#define SOFT_NAME "N@ToMi "
#define SOFT_VERSION 0.31
#define NatExprPrec 50
#define NatErrorSuffix "_error"
#define DEFAULT_STRING "N/A"
#define DEFAULT_SEPARATOR '\t'
#define COMMENT_SYMBOL '#'
#define UNINDEXED -1

#endif
