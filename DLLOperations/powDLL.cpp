#include "BaseMath.h"


class Pow : public IBaseMath {

public:

	~Pow() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override { 
		return std::make_pair(OPERATION_ERROR::SUCCESS, std::pow(params[0], params[1]));
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::POW; }

	virtual int GetNumOfArguments() override { return 2; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "^"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Pow;
}