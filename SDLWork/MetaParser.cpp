#include "stdafx.h"
#include "MetaParser.h"
#include <iostream>

using namespace std;

MetaParser::MetaParser(void ) {
	
	
}


MetaParser::~MetaParser(void){
	fclose(file);
}

void MetaParser::parse( const char* filename ) {
	this->filename = filename;
	errno_t file_open_err = fopen_s(&file, filename, "r");
	if(file_open_err != 0) {
		cerr << "Can't open meta file: " << filename;
		return;
	}

	char done = 0;
	char error = 0;
	yaml_token_type_t prevType = YAML_STREAM_START_TOKEN;

	yaml_parser_initialize(&parser);
	yaml_parser_set_input_file(&parser, file);

	while (!done)
	{
		if (!yaml_parser_scan(&parser, &token)) {
			error = 1;
			break;
		}
		onToken(&token, prevType);
		done = (token.type == YAML_STREAM_END_TOKEN);

		prevType = token.type;

		yaml_token_delete(&token);


	}

	yaml_parser_delete(&parser);

	fclose(file);

}

void MetaParser::onToken( yaml_token_t *token, yaml_token_type_t prevType ) {
	if(token->type == YAML_SCALAR_TOKEN) { //scalar token
		switch (prevType) {
		case YAML_KEY_TOKEN:
			lastKey = string((char*)token->data.scalar.value);
			break;
		case YAML_VALUE_TOKEN:
			onValueRead(&getPath(&blockKeys), &lastKey, new string((char*)token->data.scalar.value));
			break;
		}
	} else { // other token
		switch(token->type) {
		case YAML_BLOCK_MAPPING_START_TOKEN:
			blockKeys.push_back(lastKey);
			break;
		case YAML_BLOCK_END_TOKEN:
			blockKeys.pop_back();
			break;
		}

	};


}

void MetaParser::onValueRead(string *path, string* key, string* value){
	string fullpath = (*path + *key);

	try {
		MetaStruct *meta = &mapping[fullpath];
		if(meta->type == MetaType::UNKNOWN) {
			throw InvalidValueTypeException("METAPARSER Warning: " + fullpath + " is not registered");
		}
		meta->set(value->c_str());
	} catch (InvalidValueTypeException& e) {
		cerr << e.what() << " File: " << filename << endl;
	} catch (std::invalid_argument) {
		cerr << key << " value has an invalid type" << " File: " << filename << endl;
	}
	

}

string MetaParser::getPath( vector<string> *path){
	string pathString = "";
	for(int i = 0; i < path->size(); i++) {
		if(path->at(i).size() > 0){
			pathString += path->at(i);
			if(i < path->size() + 1)
				pathString += ":";
		}

	}

	return pathString;
}

void MetaParser::addMapping( const char* keypath, int *pointer ){
	mapping[keypath] = MetaStruct(pointer);
}
void MetaParser::addMapping( const char* keypath, float *pointer ){
	mapping[keypath] = MetaStruct(pointer);
}
void MetaParser::addMapping( const char* keypath, double *pointer ){
	mapping[keypath] = MetaStruct(pointer);
}
void MetaParser::addMapping( const char* keypath, string *pointer ){
	mapping[keypath] = MetaStruct(pointer);
}




