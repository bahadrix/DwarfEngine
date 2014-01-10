#pragma once
#include "YAMLMapper.h"
#include <map>
#include <iostream>

using namespace std;
class Config :	public YAMLMapper {
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

