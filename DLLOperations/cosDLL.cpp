#include "BaseMath.h"


class Cos : public IBaseMath {

public:

	~Cos() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override { 
		return std::make_pair(OPERATION_ERROR::SUCCESS, cos(params[0]));
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::FUNC; }

	virtual int GetNumOfArguments() override { return 1; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "cos"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Cos;
}