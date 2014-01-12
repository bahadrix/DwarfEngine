#include "stdafx.h"
#include "MetaStruct.h"


MetaStruct::MetaStruct(void){
	type = MetaType::UNKNOWN;
	targetIdx = 0;
}



MetaStruct::MetaStruct(int* pointer, unsigned int targetIdx /*= 0*/ ) {
	this->pointer = pointer;
	this->type = MetaType::INT;
	this->targetIdx = targetIdx;
}

MetaStruct::MetaStruct(string* pointer, unsigned int targetIdx /*= 0*/ ) {
	this->pointer = pointer;
	this->type = MetaType::STRING;
	this->targetIdx = targetIdx;
}

MetaStruct::MetaStruct(float* pointer, unsigned int targetIdx /*= 0*/ ) {
	this->pointer = pointer;
	this->type = MetaType::FLOAT;
	this->targetIdx = targetIdx;
}

MetaStruct::MetaStruct(double* pointer, unsigned int targetIdx /*= 0*/ ) {
	this->pointer = pointer;
	this->type = MetaType::DOUBLE;
	this->targetIdx = targetIdx;
}


void MetaStruct::set(const char* str){
	switch (this->type) {
	case MetaStruct::MetaType::INT:
		{
			int *value = (int*)pointer;
			*value = std::stoi(str);
		}
		break;
	case MetaStruct::MetaType::FLOAT:
		{
			float *value = (float*)pointer;
			*value = std::stof(str);
		}
		break;
	case MetaStruct::MetaType::DOUBLE:
		{
			double *value = (double*)pointer;
			*value = std::stod(str);
		}
		break;
	case MetaStruct::MetaType::STRING:
		{
			string *value = (string*)pointer;
			*value = str;
		}
		break;
	default:
		break;
	}

}

MetaStruct::~MetaStruct(void){}

