
/*
  project-1.c

  MY NAME: Luke Kraus
  MY PITT EMAIL: lek81@pitt.edu

  As you develop and test this file:

  use this command to compile: (you can name the executable whatever you like)
  gcc -W -Wall -Wextra -O2   project-1.c   -o project-1.exe

  use this command to execute:  (you will of course test on both input files)

  ./project-1.exe  sine-1.bin 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[])
{
  FILE * inFile= NULL;

  // DECLARE ALL ADDITIONAL NEEDED VARIABLES
short int prev, current;
int counter;
int direction = 0; 
int flag = 0;
int counter2 = 0;
int high = 0;
int low = 0;
int waveCount =0;

  /* recommend declaring two short int i.e prev & current so that you can compare
     them to look for zero crossings or changes in direction and sign.
     You will also need some int counters etc.
  */
  if (argc < 2)
    {
      fprintf(stderr,"\nMust specify a binary file on the command line. Please try again.\n");
      exit(EXIT_FAILURE);
    }
  if  ((inFile = fopen(argv[1],"rb")) == NULL)
    {
      fprintf(stderr,"Can't open %s for input\n", argv[1] );
      exit(EXIT_FAILURE);
    }

  // YOUR CODE HERE - READ EACH VALUE FROM THE BINARY FILE ONE AT A TIME AND LOOK FOR ZERO CROSSINGS TO DETECT WAVES
  
//read in the first value and set it equal to prev. also increase the counter to 1 because one item has been read in  
counter = 1;
fread(&prev, sizeof(prev),1,inFile );
//while the file has another line read the value into current. increase the counter as well as the wavelength counter (counter2)
while(fread(&current, sizeof(current),1,inFile )){
counter++;
counter2++;

//if direction == 0 than it is on the upward assent and if it is == 1 than it is trending down
if(direction == 0){
if(prev >current){
direction = 1;
}
}
else if(direction == 1){
if(prev < current){
direction = 0;
}
}
//sets the high and low values by comparing them to current
if(current > high){
high = current;
}
if(current < low){
low = current;
}


//detecting waves
//sets the flag to 1 if a new wave is beginning 
if(direction == 0 && (prev< 0 && current >= 0)){
flag = 1;
}
//if it is inside of a wave that we are tracking
if(flag == 1){

// if the wave is over
if((prev <0 && current >=0)){
//if not the first wave (which we dont track becuase it is not a full wave)
if(waveCount != 0){
//if current is equal to zero than we have to add 1 to counter 2 because it is the start and end of the next wave
//if it is not equal to zero than we have to take one away from the overall counter because it has not crossed it yet
if(current!=0){
printf("%d\t %hi\t %d\t %hi\t %hi\n", (counter-1),prev, counter2, high, low);
}else{
printf("%d\t %hi\t %d\t %hi\t %hi\n", (counter), current, (counter2+1), high, low);
}
}
//reset the variables for the next wave
counter2 =0 ;
waveCount++;
flag=0;
high = 0;
low = 0;

}
}
//after each iteration of the loop set prev equal to current so it can be used for comparison for the next value
prev = current;


}


  fclose(inFile); /* after the read loop is done. close file */

  return EXIT_SUCCESS;  // this is just a zero value. In C a zero return often indicates no error
}

