#include "BaseMath.h"


class UnaryMinus : public IBaseMath {

public:

	~UnaryMinus() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override {
		return std::make_pair(OPERATION_ERROR::SUCCESS, -params[0]);
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::UNARY_PLUS_OR_MINUS; }

	virtual int GetNumOfArguments() override { return 1; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "-"; }

};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new UnaryMinus;
}