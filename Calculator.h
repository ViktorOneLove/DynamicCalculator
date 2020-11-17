#pragma once
#include "Definitions.h"


enum class ERROR_T {
	SUCCESS,
	FAILURE
};


class Calculator {

public:

	void Process(std::string filePath);


private:

	/**
	* all operations from dll
	*/
	std::vector <std::pair<HINSTANCE, IBaseMath*>> validOperations;

	std::stack <double> operands;

	std::stack <IBaseMath*> operations;


	void WriteOutput(double num);


	bool IsSpace(char val) { return val == ' '; }

	/**
	* parse expression and calculate it
	*/
	ERROR_T ProcessString(std::string expression);

	/**
	* is used when a closed bracket was found in an expression
	* extract all operations and apply them until opened bracket is found
	*/
	ERROR_T ProcessClosedBracket();

	/**
	* do RPN operation logic
	* and call function that really apply(count value) function from dll's
	*/
	ERROR_T ApplyOperation(IBaseMath* curOperation);

	/**
	* get neccessary operands from stack of operands and 
	* apply operation from dll
	*/
	ERROR_T ProcessOperation(IBaseMath* operation);

	/**
	* load all dll files from folder
	*/
	ERROR_T LoadAllDLL(std::string filePath);

	/**
	* free all dll files 
	*/
	ERROR_T FreeAllDLL();

	/**
	* find instance(-s) of operation class(-es) from dll's
	* by character(-s) of an expression string
	*/
	ERROR_T ExtractOperations(const std::string& str, std::vector<IBaseMath*>& operations, bool& unaryOpMarker, int* counter);

	/**
	* find instance of operation class from dll's
	* by it's token from expression string
	*/
	IBaseMath* FindOperationByToken(std::string token, bool& unaryOpMarker);

	/**
	* find operand from expression string
	*/
	ERROR_T ExtractOperand(const std::string& str, double* operand, int* counter);


};