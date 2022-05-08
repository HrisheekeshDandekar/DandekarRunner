#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

bool check_correct_usage(int argc, char** argv);
bool run(int argc, char** argv);
char* set_command(int argc, char** argv);
void outtait();

int main(int argc, char** argv)
{

	//Check correct arguments passed and filename is correct
	if( !check_correct_usage(argc, argv) ) { return 1; }

	//Compile and run code with gcc and standard flags
	if( !run(argc, argv) ) { return 1; }
	
	return 0;
}

bool check_correct_usage(int argc, char** argv)
{
	//Checking total arguments
	if( argc != 2 )
	{
		printf("[ ERROR ] incorrect use of runner\n",
		       "[ Usage ] ./runner <filename.c>\n");
		return false;
	}
	
	//Checking file-extension
	if( strcmp((char*)&argv[1][ strlen(argv[1]) - 2 ], ".c") )
	{
		printf("[ ERROR ] Wrong filenname passed\n");
		printf("[ Usage ] ./runner <filename.c>\n"); 
		printf(".... Filename must end with .c ....\n");
		return false;
	}

	printf("File-checks passed\n");
	return true;
}

bool run(int argc, char** argv)
{
	char* run_command;
	run_command = set_command(argc, argv);
	if( system(run_command) )
	{
		printf("\nCompilation FAILED\n");
		return false;
	}
	return true;
}

#if defined(_WIN32) || defined(WIN32)		//Checking for windows
#define LINUX 0

//Compile and run for WINDOWS
char* set_command(int argc, char** argv)
{
	// --- SETTING COMMAND SIZE ---
	//|        (1)|      (2)    |    (3)   |4 |  (5)   |6|   (7)       |
	//command: gcc -Wall -Werror filename.c -o filename ; ./filename.exe
	//sizes  : 4___6_____8_______f_size+1___3__f_size-1_2_f_name+4
	//command size = 27 + (filename_size * 2)
	//
	//
	//code:  name:        size:
	//(1) -> compiler ----- [4]
	//(2) -> flags -------- [14]
	//(3) -> filename_c --- [size+1]
	//(4) -> optimization - [3]
	//(5) -> filename_raw - [size-1]
	//(6) -> pipying ------ [2]
	//(7) -> execute ------ [size+4]

	int filename_size = strlen(argv[1]);
	int command_size = (filename_size * 2) + 27;
	char* fnl_command = (char*)malloc(command_size * sizeof(char));

	//--- CREATING FINAL COMMAND ---

	//Compiler ( make it dynamic later ) 
	char* compiler = "gcc";

	//Flags ( read from file later )
	char* flags= "-Wall -Werror -o";

	//Allocate memory and set without extension
	char* filename_raw = (char*)malloc((filename_size - 2) * sizeof(char));
	for( int i = 0; i < filename_size - 2; i++ )
		filename_raw[i] = argv[1][i];

	//Windows executable program name (.exe)
	char* execute_name = (char*)malloc((filename_size 

	return fnl_command;
}

#elif defined __linux__		//Checking for linux 
#define LINUX 1

//Compile and run for WINDOWS
char* set_command(int argc, char** argv)
{
	char* fnl_command;
	return fnl_command;
}

#endif
