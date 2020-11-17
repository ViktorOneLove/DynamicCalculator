
#include "Calculator.h"


typedef IBaseMath* (*baseMathFactory)();


int main() {

	Calculator calc;

	calc.Process("plugins");

	//calc.Process();

	/*calc.LoadAllDLL();

	HINSTANCE hdll = NULL;

	hdll = ::LoadLibrary(L"D\\Programming\\C_or_C++\\Calculator\\Calculator\\plugins\\sinDLL.dll");

	baseMathFactory factoryFunc = (baseMathFactory)(
		::GetProcAddress(hdll, "createClass"));

	IBaseMath* instance = factoryFunc();

	instance->Destroy();

	FreeLibrary(hdll);*/


	return 0;
}