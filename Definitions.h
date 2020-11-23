#pragma once
#include "plugins\BaseMath.h"
#include <stack>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <filesystem>
#include <utility>


typedef IBaseMath* (*baseMathFactory)();
