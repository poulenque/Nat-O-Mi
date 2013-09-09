#ifndef PARSER_HPP
#define PARSER_HPP
#include "yaml-cpp/yaml.h"
#include "Tool.hpp"
#include <fstream>

// our data types
struct TimeConfig 
{
   double tEnd,dt_from, dt_to, dt_steps,epsilon;
   bool dt_vary;
};

struct Config 
{
   std::string name;
   std::string outpath;
   TimeConfig time_config;
   std::vector <Object> objvec;
   double G,outmodulo;
};

void operator >> (const YAML::Node& node, TimeConfig& delta_t);
void operator >> (const YAML::Node& node, Object& obj);
void operator >> (const YAML::Node& node, Config& conf);
void configFileParser(const std::string inputPath,Config& config);
std::string floatToString(float number);


#endif
