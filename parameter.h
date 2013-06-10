/*! \file parameter.h 
 * \brief Headerfile for input parameter data class 
 * 
 * Use parameters to easily load and save simulation parameters.  Two special cases are included:
 *
 * Interactive mode:
 *     ./commandname -interactive 1
 *
 * File mode:
 *     ./commandname -paramfile filename.txt
*/

#ifndef parameter_h__ 
#define parameter_h__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>

class paramBase
{
	public:
		virtual void print( void) = 0;
		virtual void assign(std::string s) = 0;
		virtual std::string tostring(void) = 0;
		std::string name;
		std::string alias;
};

template < class T> class param:public paramBase
{
	public:

		param(T* pointer) { value = pointer; };
		param(T* pointer, const char * n) { value = pointer; name=n; };
		param(T* pointer, const char * n, const char * a) { value = pointer; name=n; alias=a; };
		
		std::string tostring(void) {
			std::ostringstream s;
			s << "-" << name << " " << *value;
			return s.str();
		}

		void print(void) { 
			std::cout << tostring() << std::endl;
		}

		void assign(std::string s) {
			std::istringstream(s) >> *value;
		}

		void setName(char * n) { name = n; }
		void setName(const char * n) { name = n; }

		T * value;
};

template <> class param<std::string>:public paramBase
{
        public:

                param(std::string* pointer) { value = pointer; };
                param(std::string* pointer, const char * n) { value = pointer; name=n; };
                param(std::string* pointer, const char * n, const char * a) { value = pointer; name=n; alias=a;};
 
                std::string tostring(void) {
                        std::ostringstream s;
                        s << "-" << name << " " << *value;
                        return s.str();
                }

                void print(void) {
			if (value->empty())
				return;
                        std::cout << tostring() << std::endl;
                }


                void assign(std::string s) {
			*value = s;
		}

                void setName(char * n) { name = n; }
                void setName(const char * n) { name = n; }

                std::string* value;
};



class paramList
{
	public:
		paramList(void) {
			interactive = 0;
			add(&interactive, "interactive"); 

			paramfile = "";
			add(&paramfile, "paramfile"); 
		}

		int usage(int argc, char * argv[]) {
			//! \todo print usage message
			return 0;
		}
			

		int parseInputs(int argc, char * argv[]) {
			//! \todo load file if argc is 2 
			int i = 1;
			while(i < argc)
        		{
                		std::string arg (argv[i]);
				bool found = false;
				for(std::vector<int>::size_type j = 0; j < params.size(); j++) {
	        	        	if( arg == "-"+params[j]->name || arg == "-"+params[j]->alias ) {
                	        		i++;
	                	        	if(i >= argc) {
        	                        		printf("ERROR - Incorrect input arguments %s\n", arg.c_str());
						} else {
							//std::string s(argv[i]);
	                	        		params[j]->assign(argv[i]);
							found = true;
						}
					}
        		        }
				if(!found) {
					std::cerr << "WARNING: option " << arg << std::endl;
				}
	               		i++;
        		}
			parseFile();
			runInteractive();
			print();
			return 0;	
		};

	/*	template <class T>
		int add(T* v, const char * n) {
			
			param <T> * op = new param<T>(v,n);
			params.push_back(op);
			return 0;
		}
*/
		template <class T>
		int add(T* v, const char * n) {
			param <T> * op = new param<T>(v,n);
			params.push_back(op);
			return 0;
		}

		int parseFile() {
			if (!paramfile.empty()) {
				std::cout << "Parcing file " << paramfile << std::endl;
				std::string filename = paramfile;
				paramfile = "";
				return parseFile(filename.c_str());	
			}
			return 0;
		}
		int runInteractive() {
			if (interactive) 
				return interactiveInterface();	
			return 0;
		}
 
		int parseFile(const char * file) { 
		        FILE* pfile;    // pointer to the file the data is being read from
	        	int argc;
        		char** argv ;
      		  	argv = (char **) malloc(sizeof(char *)* 256);
		                
		        // opens input stream used to read in
		        pfile = fopen(file,"r");
		        if(pfile==NULL)
		        {
		                printf("ERROR - file %s not found\n", file);
		                return 1;
		        }
		        //argv = (char**)malloc(256 * sizeof(char));
		        for(int i = 0; i < 256; i++)
		                argv[i] = (char*)malloc(256 * sizeof(char));

		        argc=1;         
		        while(fscanf(pfile, "%s", argv[argc]) != EOF) {
                		if(argv[argc] != NULL) {
		                        argc++; 
                		}       
        	
			}
			return parseInputs(argc, argv);
		};   


		int interactiveInterface(void) {
			while (1) {
				std::cout << std::endl << "Modify Parameters:" << std::endl;
				for(std::vector<int>::size_type i = 0; i < params.size(); i++) {
					std::cout << "\t[" << i << "]\t" << params[i]->tostring() << std::endl;
				}
				std::cout << "\t[r] Run simulation" << std::endl;
				std::cout << "\t[e] Exit" << std::endl;
				std::cout << "\t[f] Load paramiter file" << std::endl;
				std::cout << "\t[s] Save parameter file" << std::endl;
				std::cout << "Enter Number to parameter to change: ";	
				std::string input;
				std::cin >> input;
				int num = atoi(input.c_str());
				if( input == "e" || input == "E" ) {
					//! \todo - Do you really want to exit.
					exit(0);
				}
				else if( input == "r" || input == "R" ) {
					return 0;
				}
				else if( input == "f" || input == "F" ) {
					//! \todo - Add option for input file.	
					std::cout << "NOT implimented yet" << std::endl;
				}
				else if( input == "s" || input == "S" ) {
					//! \todo - Add option to save file.	
					std::cout << "NOT implimented yet" << std::endl;
				}
				else if(num > -1 && num <= params.size()) {
					std::cout << "New Value for ";
					params[num]->print();
					std::cin >> input;
					params[num]->assign(input.c_str());
				}
			} 
			return 0;
		}

		void print(void) {
			for(std::vector<int>::size_type i = 0; i < params.size(); i++) {
				params[i]->print();
			}
		}

		int save(const char * filename) {
			FILE * fid = fopen(filename, "w");
			if(fid == NULL) {
				std::cerr << "ERROR: unable to oupen file" << std::endl;
				return 1;
			}
			
			for(std::vector<int>::size_type i = 0; i < params.size(); i++) {
				fprintf(fid, "%s\n", params[i]->tostring().c_str());
			}
			fclose(fid);
			return 0;
		}

	
	private:
		std::string paramfile;
		bool interactive;
		std::vector<paramBase *> params;
};

#endif // parameter_h__ 

