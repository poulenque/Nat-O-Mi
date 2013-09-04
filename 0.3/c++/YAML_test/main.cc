#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>    

// our data models
struct Vec3
{
	float x, y, z;
};

struct Power
{
	std::string name;
	int damage;
};
struct Monster {
	std::string name;
	Vec3 position;
	std::vector <Power> powers;
};

// operators for parsing
void operator >> (const YAML::Node& node, Vec3& v)
{
	node[0] >> v.x;
	node[1] >> v.y;
	node[2] >> v.z;
}

void operator >> (const YAML::Node& node, Power& power)
{
	node["name"] >> power.name;
	node["damage"] >> power.damage;
}

void operator >> (const YAML::Node& node, Monster& monster)
{
	node["name"] >> monster.name;
	node["position"] >> monster.position;
	const YAML::Node& powers = node["powers"];
	for(unsigned i = 0; i < powers.size(); i++)
	{
		Power power;
		powers[i] >> power;
		monster.powers.push_back(power);
	}
}

// operators for emitting
YAML::Emitter& operator << (YAML::Emitter& out, const Vec3& v)
{  
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}
 
YAML::Emitter& operator << (YAML::Emitter& out, const Power& power)
{
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << power.name;
	out << YAML::Key << "damage";
	out << YAML::Value << power.damage;
	out << YAML::EndMap;
	return out;
}
 
YAML::Emitter& operator << (YAML::Emitter& out, const Monster& monster)
{
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << monster.name;
	out << YAML::Key << "position";
	out << YAML::Value << monster.position;
	out << YAML::Key << "powers";
	out << YAML::Value;
	out << YAML::BeginSeq;
	for(size_t pidx = 0; pidx < monster.powers.size(); ++pidx)
	{
		out << monster.powers[pidx];
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
	return out;
}
 
 
int main()
{
	// std::string monsters_yaml("- name: Ogre\n  position: [0, 5, 0]\n  powers:\n    - name: Club\n      damage: 10\n    - name: Fist\n      damage: 8\n- name: Dragon\n  position: [1, 0, 10]\n  powers:\n    - name: Fire Breath\n      damage: 25\n    - name: Claws\n      damage: 15\n- name: Wizard\n  position: [5, -3, 0]\n  powers:\n    - name: Acid Rain\n      damage: 50\n    - name: Staff\n      damage: 3\n");
	// // std::string monsters_yaml("- n: Ogre\n  position: [0, 5, 0]\n  powers:\n    - n: Club\n      damage: 10\n    - n: Fist\n      damage: 8\n- n: Dragon\n  position: [1, 0, 10]\n  powers:\n    - n: Fire Breath\n      damage: 25\n    - n: Claws\n      damage: 15\n- n: Wizard\n  position: [5, -3, 0]\n  powers:\n    - n: Acid Rain\n      damage: 50\n    - n: Staff\n      damage: 3\n");

	// // write out the monster.yaml
	// std::ofstream monsters_yaml_file;
	// monsters_yaml_file.open("monsters.yaml");
	// monsters_yaml_file << monsters_yaml;
	// monsters_yaml_file.close();
 
	// list of monsters
	std::vector<Monster> monsters;
 
	// read in the the monster.yaml
	std::ifstream fin("monsters.yaml");
	YAML::Parser parser(fin);
	YAML::Node doc;
	parser.GetNextDocument(doc);
	for(size_t i = 0; i < doc.size(); i++)
	{
		Monster monster;
		doc[i] >> monster;
		monsters.push_back(monster);
		std::cout<< "### : " << monster.name << std::endl;
	}
 
	YAML::Emitter out;
	out << YAML::BeginSeq;
	for(size_t i = 0; i < monsters.size(); i++)
	{
		out << monsters[i];
	}
	out << YAML::EndSeq;
 
//    std::cout << out.c_str() << std::endl;
	return 0;
}