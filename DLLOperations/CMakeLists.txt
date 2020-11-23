# CMakeList.txt: проект CMake для CalculatorDLL; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.

add_library (sinDLL SHARED sinDLL.cpp BaseMath.h)

add_library (cosDLL SHARED cosDLL.cpp BaseMath.h)


add_library (binaryPlusDLL SHARED binaryPlusDLL.cpp BaseMath.h)

add_library (binaryMinusDLL SHARED binaryMinusDLL.cpp BaseMath.h)


add_library (unaryPlusDLL SHARED unaryPlusDLL.cpp BaseMath.h)

add_library (unaryMinusDLL SHARED unaryMinusDLL.cpp BaseMath.h)


add_library (openBracketDLL SHARED openBracketDLL.cpp BaseMath.h)

add_library (closeBracketDLL SHARED closeBracketDLL.cpp BaseMath.h)


add_library (powDLL SHARED powDLL.cpp BaseMath.h)

add_library (multiplicationDLL SHARED multiplicationDLL.cpp BaseMath.h)

add_library (divisionDLL SHARED divisionDLL.cpp BaseMath.h)


add_library (piDLL SHARED piDLL.cpp BaseMath.h)


# TODO: Добавьте тесты и целевые объекты, если это необходимо.
