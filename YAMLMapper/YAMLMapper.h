#pragma once
#ifdef YAMLMAPPER_EXPORTS
#define YAMLMAPPER_API __declspec(dllexport)
#else
#define YAMLMAPPER_API __declspec(dllimport)
#endif

#include <yaml.h>
#include <vector>
#include <string>
#include <map>
#include "MetaStruct.h"

using namespace std;

class KeyNotRegisteredWarningException : public std::runtime_error {
public:
	KeyNotRegisteredWarningException(const string& message) 
		: std::runtime_error(message) { };
};

class YAMLMAPPER_API YAMLMapper {

public:

	YAMLMapper(void);
	~YAMLMapper(void);
	void parse(const char* filename);
	
	void addMapping(string keypath, int *pointer, unsigned int targetIdx = 0);
	void addMapping(string keypath, float *pointer, unsigned int targetIdx = 0);
	void addMapping(string keypath, double *pointer, unsigned int targetIdx = 0);
	void addMapping(string keypath, string* pointer, unsigned int targetIdx = 0);


private:
	yaml_parser_t parser;
	yaml_token_t token;
	FILE *file;
	string filename;
	unsigned int currentFlowIdx;

protected:
	void onToken(yaml_token_t *token, yaml_token_type_t prevType);
	void onValueRead(string *path, string* key, string* value, unsigned int targetIdx = 0);
	vector<string> blockKeys;
	string lastBlockKey, lastKey;

	static string getPath(vector<string> *path);

	std::map<string, MetaStruct> mapping;

};









