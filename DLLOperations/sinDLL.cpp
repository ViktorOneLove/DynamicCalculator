#include "BaseMath.h"


class Sin : public IBaseMath {

public:

	~Sin() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override { 
		return std::make_pair(OPERATION_ERROR::SUCCESS, sin(params[0]));
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::FUNC; }

	virtual int GetNumOfArguments() override { return 1; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "sin"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Sin;
}