#pragma once
#include "metaparser.h"
#include <map>
#include <iostream>

using namespace std;
class Config :	public MetaParser {
public:
	
	Config(void);
	~Config(void);
	struct WindowStruct {
		string title;
		int width;
		int height;
	} window;
private:
	
	
};

