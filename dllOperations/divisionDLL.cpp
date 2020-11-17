#include "BaseMath.h"


class Division : public IBaseMath {

public:

	~Division() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override {
		if(params[1] == 0)
			return std::make_pair(OPERATION_ERROR::DIVISION_BY_ZERO, NONE);
		return std::make_pair(OPERATION_ERROR::SUCCESS, params[0] / params[1]);
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::MULTIPLICATION_OR_DIVISION; }

	virtual int GetNumOfArguments() override { return 2; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "/"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Division;
}