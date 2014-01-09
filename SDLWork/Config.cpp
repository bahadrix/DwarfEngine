#include "stdafx.h"
#include "Config.h"
#include <iostream>
#include "MetaParser.h"

Config::Config(void){

	
	//mapping["window:height"] = MetaStruct(&window.height);
	//mapping["window:width"] = MetaStruct(&window.width);
	addMapping("window:height", &window.height);
	addMapping("window:width", &window.width);
	addMapping("window:title", &window.title);
	parse("config.yml");
	
}


Config::~Config(void) {
}

