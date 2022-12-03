#include "Config.h"
#include <iostream>
#include "test.h"

int main(int argc, char* argv[]) {
	std::cout << "Running: " << argv[argc-argc] << " Version: " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	std::cout << "Hello, World!" << std::endl;		
	Test test;
	test.value = 2;
	std::cout << "2 + 2 = " << test.iterated_value(2) << std::endl;
	return 0;
}

