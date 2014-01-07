#pragma once
#include "metaparser.h"

using namespace std;
class Config :	public MetaParser {
public:
	
	Config(void);
	~Config(void);
	virtual void onValueRead(string *path, string* key, string* value);
	struct WindowStruct {
		int width;
		int height;
	} Window;
private:
	

};

