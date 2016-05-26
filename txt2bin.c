/*  txt2bin.c

  MY NAME: Luke Kraus
  MY PITT EMAIL: lek81@pitt.edu

  As you develop and test this file:

  use this command to compile: (you can name the executable whatever you like)
		gcc -W -Wall -Wextra -O2  txt2bin.c  -o txt2bin.exe

  use this command to execute:  (you will of course test on both input files)
		txt2bin.exe sine-1.bin
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] )
{	
	FILE* txtFile, *binFile;
	short int shortVal;
	
	
	if (argc<3)
	{
		printf("usage: %s  <infilename> <outfilename> (i.e. ./txt2bin.exe sine-1.txt sine-1.bin)\n", argv[0] );
		return EXIT_FAILURE;
	}
	
	txtFile = fopen( argv[1], "rt" );
	if (txtFile == NULL )
	{
		printf("Can't open %s for input. Program halting\n",argv[1] );
		return EXIT_FAILURE;
	}
	
	binFile = fopen( argv[2], "wb" );
	if (binFile == NULL )
	{
		printf("Can't open %s for output. Program halting\n",argv[2] );
		return EXIT_FAILURE;
	}
	
	
	//write the value to the binary file as long as there is still ints in the file
	
	while(fscanf (txtFile, "%hi",&shortVal ) != EOF){
	
		//writes the data from the txt file to the binary file
		fwrite(&shortVal, sizeof(shortVal),1,binFile);
	
	}
	
	
	//closes the txt file and binary file
	fclose( txtFile );
	fclose( binFile );
	
	
	//open the binary file
	binFile = fopen(argv[2], "rb");

	//while the file has lines left read the value into shortVal
	
	while((fread(&shortVal,sizeof(shortVal) ,1,binFile ))){
		//print the value to the stdout
		printf("%hi\n", shortVal);
	
	}


	fclose( binFile);

	return EXIT_SUCCESS;  // 0 value return means no errors
}

