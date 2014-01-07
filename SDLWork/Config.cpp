#include "stdafx.h"
#include "Config.h"

#define CONFIG_WINDOW_WIDTH "window::width"
Config::Config(void){
	blockKeys.push_back(string("root"));
	parse("config.yml");
}


Config::~Config(void)
{
}


void Config::onValueRead(string *path, string* key, string* value) {
	string fullpath = *path + *key;
	
	printf("\n%s = %s", fullpath.c_str(), value->c_str());

	
}
