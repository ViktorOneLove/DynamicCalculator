#include "BaseMath.h"


class Multiplication : public IBaseMath {

public:

	~Multiplication() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override { 
		return std::make_pair(OPERATION_ERROR::SUCCESS, params[0] * params[1]);
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::MULTIPLICATION_OR_DIVISION; }

	virtual int GetNumOfArguments() override { return 2; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "*"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Multiplication;
}