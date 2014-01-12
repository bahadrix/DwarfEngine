// YAMLMapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "YAMLMapper.h"
#include <iostream>

using namespace std;

YAMLMapper::YAMLMapper(void ) {


}


YAMLMapper::~YAMLMapper(void){
	fclose(file);
}

void YAMLMapper::parse( const char* filename ) {
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

	currentFlowIdx = 0;

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

void YAMLMapper::onToken( yaml_token_t *token, yaml_token_type_t prevType ) {
	if(token->type == YAML_SCALAR_TOKEN) { //scalar token
		if(prevType == YAML_KEY_TOKEN) {
			lastKey = string((char*)token->data.scalar.value);
		} else if (prevType == YAML_VALUE_TOKEN || prevType == YAML_FLOW_SEQUENCE_START_TOKEN || prevType == YAML_FLOW_ENTRY_TOKEN) {
			onValueRead(&getPath(&blockKeys), &lastKey, new string((char*)token->data.scalar.value), currentFlowIdx);
		}

	} else { // other token
		switch(token->type) {
		case YAML_BLOCK_MAPPING_START_TOKEN:
			blockKeys.push_back(lastKey);
			break;
		case YAML_BLOCK_SEQUENCE_START_TOKEN:
			blockKeys.push_back(lastKey);
			break;
		case YAML_BLOCK_END_TOKEN:
			blockKeys.pop_back();
			break;
		case YAML_FLOW_ENTRY_TOKEN:
			currentFlowIdx++;
			break;
		case YAML_FLOW_SEQUENCE_END_TOKEN:
			currentFlowIdx = 0;
			break;
		}

	};


}

void YAMLMapper::onValueRead(string *path, string* key, string* value, unsigned int targetIdx /* = 0*/){
	string fullpath = (*path + *key + ":[" + to_string(targetIdx) + "]");

	try {
		MetaStruct *meta = &mapping[fullpath];
		
		if(meta == NULL || meta->type == MetaStruct::MetaType::UNKNOWN) {
			throw KeyNotRegisteredWarningException(fullpath);
		}
		meta->set(value->c_str());
	} catch (KeyNotRegisteredWarningException& e) {
		cerr << "YM:KeyNotRegistered:" << e.what() << " File: " << filename << endl;
	} catch (std::invalid_argument) {
		cerr << key << " value has an invalid type" << " File: " << filename << endl;
	}
}

string YAMLMapper::getPath( vector<string> *path){
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

void YAMLMapper::addMapping( string keypath, int *pointer, unsigned int targetIdx /*= 0*/ ){
	mapping[keypath + ":[" + to_string(targetIdx) + "]"] =  MetaStruct(pointer);
}
void YAMLMapper::addMapping( string keypath, float *pointer, unsigned int targetIdx /*= 0*/ ){
	mapping[keypath + ":[" + to_string(targetIdx) + "]"] =  MetaStruct(pointer);
}
void YAMLMapper::addMapping( string keypath, double *pointer, unsigned int targetIdx /*= 0*/ ){
	mapping[keypath + ":[" + to_string(targetIdx) + "]"] =  MetaStruct(pointer);
}
void YAMLMapper::addMapping( string keypath, string *pointer, unsigned int targetIdx /*= 0*/ ){
	mapping[keypath + ":[" + to_string(targetIdx) + "]"] =  MetaStruct(pointer);
}




