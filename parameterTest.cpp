#include "parameter.h"
#include <vector>

int main(int argc, char *argv[]) {
	int test = 0;
	std::cout << "Testing = " << test << std::endl;		

	std::vector<paramBase *> params;
	param <int> op(&test);
	
	op.name = "bob";
	op.alias = "b";

	params.push_back((paramBase *) &op);	

	//op.assign(2);
	std::cout << "Testing = " << test << std::endl;		

	op.print();

        std::cout << "Setting up simulation parametersd " << argc << std::endl;
        int i=1;
        while(i < argc)
        {
                std::string arg (argv[i]);
                std::cout << "testing " << arg << std::endl;
		if( arg == "-"+op.name || arg == "-"+op.alias ) {
        		std::cout << "found " << op.name << std::endl;
	                i++;
                        if(i >= argc) {
                                printf("ERROR - Incorrect input arguments %s\n", arg.c_str());
                                return 1;
                        }
			op.assign(argv[i]);
		}
		i++;
	}
	std::cout << "Testing = " << test << std::endl;		

	//if(test != 2)
	//	return 1;
	
	return 0;
}
