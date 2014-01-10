#pragma once
#include <yaml.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

class InvalidValueTypeException : public std::runtime_error {
public:
	InvalidValueTypeException(const string& message) 
		: std::runtime_error(message) { };
};

class MetaParser {

public:

	MetaParser(void);
	~MetaParser(void);
	void parse(const char* filename);
	

private:
	yaml_parser_t parser;
	yaml_token_t token;
	FILE *file;
	string filename;

protected:
	void onToken(yaml_token_t *token, yaml_token_type_t prevType);
	void onValueRead(string *path, string* key, string* value);
	vector<string> blockKeys;
	string lastBlockKey, lastKey;

	static string getPath(vector<string> *path);
	static enum class MetaType {INT, FLOAT, DOUBLE, STRING, UNKNOWN};
	void addMapping(const char* keypath, int *pointer);
	void addMapping(const char* keypath, float *pointer);
	void addMapping(const char* keypath, double *pointer);
	void addMapping(const char* keypath, string* pointer);
	static struct MetaStruct {

		void* pointer;
		MetaType type;

		MetaStruct(void){
			type = MetaType::UNKNOWN;

		}

		MetaStruct(int* pointer) {
			this->pointer = pointer;
			this->type = MetaType::INT;
		}

		MetaStruct(string* pointer) {
			this->pointer = pointer;
			this->type = MetaType::STRING;
		}
		MetaStruct(float* pointer) {
			this->pointer = pointer;
			this->type = MetaType::FLOAT;
		}
		MetaStruct(double* pointer) {
			this->pointer = pointer;
			this->type = MetaType::DOUBLE;
		}

		void set(const char* str){
			switch (this->type) {
			case MetaParser::MetaType::INT:
				{
					int *value = (int*)pointer;
					*value = std::stoi(str);
				}
				break;
			case MetaParser::MetaType::FLOAT:
				{
					float *value = (float*)pointer;
					*value = std::stof(str);
				}
				break;
			case MetaParser::MetaType::DOUBLE:
				{
					double *value = (double*)pointer;
					*value = std::stod(str);
				}
				break;
			case MetaParser::MetaType::STRING:
				{
					string *value = (string*)pointer;
					*value = str;
				}
				break;
			default:
				break;
			}

		}
	};
	std::map<string, MetaStruct> mapping;

};




