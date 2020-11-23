#include "BaseMath.h"



class Pi : public IBaseMath {

	~Pi() {};

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double> params) override {
		return std::make_pair(OPERATION_ERROR::SUCCESS, M_PI);
	}

	virtual int GetOperationPrioraty() override { return OPERATION_TYPE::CONSTANT; }

	virtual int GetNumOfArguments() override { return 0; }

	virtual void Destroy() override { delete this; }

	virtual std::string GetFuncToken() override { return "pi"; }
};

extern "C" __declspec(dllexport) IBaseMath * __cdecl createClass()
{
	return new Pi;
}