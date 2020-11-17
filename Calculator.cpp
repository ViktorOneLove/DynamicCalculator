#include "Calculator.h"



void Calculator::Process(std::string filePath) {

	if (LoadAllDLL(filePath) == ERROR_T::FAILURE)
		return;

	std::string expression;
	while (std::getline(std::cin, expression)) {
		if (ProcessString(expression) == ERROR_T::FAILURE) {
			std::cout << "error" << "\n" << std::endl;
			while (!operations.empty())
				operations.pop();
			while (!operands.empty())
				operands.pop();
		}
	}

	FreeAllDLL();
	return;
}


void Calculator::WriteOutput(double num) {
	std::cout << num << "\n" << std::endl;
}


ERROR_T Calculator::ProcessString(std::string expression) {
	int i = 0;
	bool unaryOpMarker = true;
	while (i < expression.length()) {
		try {

			if (!IsSpace(expression[i])) {

				if (isdigit(expression[i])) {
					double operand;
					if (ExtractOperand(expression, &operand, &i) == ERROR_T::FAILURE)
						return ERROR_T::FAILURE;
					operands.push(operand);
					unaryOpMarker = false;
				}
				//anyway this might be a function from dll
				else {
					std::vector<IBaseMath*> curOperations;

					if (ExtractOperations(expression, curOperations, unaryOpMarker, &i) == ERROR_T::FAILURE)
						return ERROR_T::FAILURE;

					for (auto op : curOperations) {
						if (ApplyOperation(op) == ERROR_T::FAILURE)
							return ERROR_T::FAILURE;
					}
				}
			}
			else {
				i++;
			}

		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << '\n';
			return ERROR_T::FAILURE;
		}

	}

	while (!operations.empty()) {
		if (ProcessOperation(operations.top()) == ERROR_T::FAILURE)
			return ERROR_T::FAILURE;
		operations.pop();
	}

	if (operands.size() != 1)
		return ERROR_T::FAILURE;

	WriteOutput(operands.top());
	operands.pop();

	return ERROR_T::SUCCESS;

}



ERROR_T Calculator::ExtractOperand(const std::string& str, double* operand, int* counter) {
	int numDots = 0;
	int begginingOfDigit = *counter;
	while (isdigit(str[*counter]) || str[*counter] == '.' && *counter < str.length()) {
		*counter += 1;
		if (str[*counter] == '.')
			numDots++;
		if (numDots > 1)
			return ERROR_T::FAILURE;
	}
	int endOfDigit = *counter;
	*operand = std::stof(str.substr(begginingOfDigit, endOfDigit - begginingOfDigit + 1));
	return ERROR_T::SUCCESS;
}


ERROR_T Calculator::ExtractOperations(const std::string& str, std::vector<IBaseMath*>& operations, bool& unaryOpMarker, int* counter) {
	std::string curOperation;

	while (!isdigit(str[*counter]) && str[*counter] != ' ' && *counter < str.length()) {
		curOperation += str[*counter];
		*counter += 1;

		IBaseMath* op = FindOperationByToken(curOperation, unaryOpMarker);

		if (op != NULL) {
			operations.push_back(op);
			curOperation.clear();
		}

	}

	if (curOperation.length() != 0)
		return ERROR_T::FAILURE;

	return ERROR_T::SUCCESS;
}


ERROR_T Calculator::ApplyOperation(IBaseMath* curOperation) {

	if (curOperation->GetFuncToken() == "(") {
		operations.push(curOperation);

	} else if (curOperation->GetFuncToken() == ")") {
		if (ProcessClosedBracket() == ERROR_T::FAILURE)
			return ERROR_T::FAILURE;

	} else if (!operations.empty() && operations.top()->GetOperationPrioraty() >= curOperation->GetOperationPrioraty()) {
		if (ProcessOperation(operations.top()) == ERROR_T::FAILURE)
			return ERROR_T::FAILURE;
		operations.pop();
		operations.push(curOperation);

	} else {
		operations.push(curOperation);
	}


	return ERROR_T::SUCCESS;

}


ERROR_T Calculator::ProcessOperation(IBaseMath* operation) {
	int numOfNecessaryOperands = operation->GetNumOfArguments();
	std::vector<double> funcOperands;

	if (numOfNecessaryOperands > operands.size())
		return ERROR_T::FAILURE;

	for (int i = 0; i < numOfNecessaryOperands; i++) {
		funcOperands.insert(funcOperands.begin(), operands.top());
		operands.pop();
	}

	std::pair<OPERATION_ERROR, double> res = operation->DoFunc(funcOperands);
	if (res.first != OPERATION_ERROR::SUCCESS)
		return ERROR_T::FAILURE;

	operands.push(res.second);

	return ERROR_T::SUCCESS;
}


ERROR_T Calculator::ProcessClosedBracket() {

	while (operations.size() > 0 && operations.top()->GetFuncToken() != "(") {
		if (ProcessOperation(operations.top()) == ERROR_T::FAILURE)
			return ERROR_T::FAILURE;
		operations.pop();
	}
	//remove '(' from stack with operations
	if (operations.size() > 0 && operations.top()->GetFuncToken() != "(" || operations.size() == 0)
		return ERROR_T::FAILURE;
	operations.pop();

	return ERROR_T::SUCCESS;
}



ERROR_T Calculator::LoadAllDLL(std::string filePath) {

	for (auto& p : std::filesystem::directory_iterator(filePath)) {

		std::string fileName = p.path().string();
		std::string fileType = fileName.substr(fileName.find_last_of('.'), fileName.length() - 1);

		if (fileType != ".dll")
			continue;

		HINSTANCE hdll = LoadLibrary(p.path().wstring().c_str());

		if (!hdll)
			return ERROR_T::FAILURE;

		baseMathFactory factoryFunc = (baseMathFactory)(
			GetProcAddress(hdll, "createClass"));

		if (!factoryFunc) {
			FreeLibrary(hdll);
			return ERROR_T::FAILURE;
		}

		validOperations.push_back(std::make_pair(hdll, factoryFunc()));

	}

}


ERROR_T Calculator::FreeAllDLL() {
	for (int i = 0; i < validOperations.size(); i++) {
		validOperations.at(i).second->Destroy();
		FreeLibrary(validOperations.at(i).first);
	}
	return ERROR_T::SUCCESS;
}


IBaseMath* Calculator::FindOperationByToken(std::string token, bool& unaryOpMarker) {
	for (int i = 0; i < validOperations.size(); i++) {

		IBaseMath* operation = validOperations.at(i).second;
		std::string funcToken = validOperations.at(i).second->GetFuncToken();

		if (token == "(" && operation->GetFuncToken() == "(") {
			unaryOpMarker = true;
			return operation;

		} else if (token == ")" && operation->GetFuncToken() == ")") {
			unaryOpMarker = false;
			return operation;

		//consts ass PI
		} else if (operation->GetNumOfArguments() == 0 && token == funcToken) {
			unaryOpMarker = false;
			return operation;

		} else if (operation->GetNumOfArguments() == 1  && unaryOpMarker && token == funcToken) {
			unaryOpMarker = true;
			return operation;

		} else if (operation->GetNumOfArguments() > 1 && !unaryOpMarker && token == funcToken) {
			unaryOpMarker = true;
			return operation;
		} 


	}
	return NULL;
}
