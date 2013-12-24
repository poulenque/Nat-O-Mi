#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.hpp"

// now the extraction operators for these types
void operator >> (const YAML::Node& node, TimeConfig& delta_t)
{
   node[0] >> delta_t.dt_from;
   node[1] >> delta_t.dt_to;
   node[2] >> delta_t.dt_steps;
}

void operator >> (const YAML::Node& node, Object& obj)
{
   node["Name"] >> obj.name;
   node["mass"] >> obj.mass;
   node["radius"] >> obj.radius; 
   node["position"][0] >> obj.position.x;
   node["position"][1] >> obj.position.y;
   node["position"][2] >> obj.position.z;
   node["speed"][0] >> obj.speed.x;
   node["speed"][1] >> obj.speed.y;
   node["speed"][2] >> obj.speed.z;
   node["outputFile"] >> obj.outfile;
}

void operator >> (const YAML::Node& node, Config& conf) 
{
   node["dt"] >> conf.time_config;
   node["varyDt"] >> conf.time_config.dt_vary;
   node["epsilon"] >> conf.time_config.epsilon;
   node["tEnd"] >> conf.time_config.tEnd;
   node["outputFolder"] >> conf.outpath;
   node["outputModulo"] >> conf.outmodulo;
   node["G"] >> conf.G;
   const YAML::Node& objs = node["Objects"];
   for(unsigned i=0;i<objs.size();i++)
   {
      Object obj;
      objs[i] >> obj;
      conf.objvec.push_back(obj);
   }
}
void configFileParser(const std::string inputPath,Config& config)
{
   try{    
     std::ifstream fin(inputPath.c_str());
     YAML::Parser parser(fin);
     YAML::Node doc;
     parser.GetNextDocument(doc);

     for(unsigned i=0;i<doc.size();i++) 
        doc[i] >> config;

    } catch(YAML::ParserException& e) { std::cout << e.what() << "\n";}
}
std::string floatToString(float number)
{
	std::ostringstream ss;
	ss << number;
	return ss.str();
}
