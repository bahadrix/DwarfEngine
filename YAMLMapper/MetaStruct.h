#pragma once
#include <string>

using namespace std;
class MetaStruct
{
public:
	static enum class MetaType {
		INT, FLOAT, DOUBLE, STRING, // Basic types
		UNKNOWN // Unknown type
	};

	
	MetaStruct(void);
	
	MetaStruct(int* pointer, unsigned int targetIdx = 0);
	MetaStruct(string* pointer, unsigned int targetIdx = 0);
	MetaStruct(float* pointer, unsigned int targetIdx = 0);
	MetaStruct(double* pointer, unsigned int targetIdx = 0);
	~MetaStruct(void);
	void set(const char* str);
	void* pointer;
	MetaType type;
private:
	unsigned int targetIdx;
friend class YAMLMapper;	
};

