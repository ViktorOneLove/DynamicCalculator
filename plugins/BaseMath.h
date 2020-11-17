#pragma once

#ifdef _DLL_
#define DECLSPEC _declspec (dllexport)
#else
#define DECLSPEC _declspec (dllimport)
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <cmath>

enum OPERATION_TYPE {
	BINARY_PLUS_OR_MINUS = 0,
	MULTIPLICATION_OR_DIVISION = 1,
	UNARY_PLUS_OR_MINUS = 2,
	POW = 3,
	FUNC = 4,
	CONSTANT = 5,
	BRACKET = -1
};

enum OPERATION_ERROR {
	SUCCESS,
	DIVISION_BY_ZERO
};


class IBaseMath {

public:

	constexpr static const float NONE = 0.0;

	virtual void Destroy() = 0;

	virtual std::pair<OPERATION_ERROR, double> DoFunc(std::vector<double>) = 0;

	virtual int GetOperationPrioraty() = 0;

	virtual int GetNumOfArguments() = 0;

	virtual std::string GetFuncToken() = 0;

};


