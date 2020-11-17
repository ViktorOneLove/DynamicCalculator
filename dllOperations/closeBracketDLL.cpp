#include "BaseMath.h"



class CloseBracket : public IBaseMath {

	~CloseBracket() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override { 
		return std::make_pair(OPERATION_ERROR::SUCCESS, NONE); 
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::BRACKET; }

	virtual int GetNumOfArguments() override { return 0; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return ")"; }

};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new CloseBracket;
}