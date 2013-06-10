#include "parameter.h"
#include <vector>
#include <string.h>

int main(int argc, char *argv[]) {

	int d = 0;
	int a = 0;
	int b = 0;
	double cc = 3.14159;
	std::string test("HelloWorld");

	paramList inputs;
	inputs.add(&a, "a");
	inputs.add(&b, "b");
	inputs.add(&d, "d");	
	inputs.add(&cc, "cc");	
	inputs.add(&test, "test");

	std::cout << "Printing Parameter List before parsing." << std::endl;
	inputs.print();

	std::cout << std::endl << "Printing Parameter List after parsing." << std::endl;
	inputs.parseInputs(argc, argv);

	//std::cout << std::endl << "Printing Parameter List after parsing." << std::endl;
	//inputs.parseFile("./testinput.txt");

	//inputs.interactive();
	

	return 0;
}
