
#include "Calculator.h"


typedef IBaseMath* (*baseMathFactory)();


int main() {

	Calculator calc;

	calc.Process("plugins");

	return 0;
}
