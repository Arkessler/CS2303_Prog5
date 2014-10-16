//  RoboMall Program
/* 
	Originally coded by Professor Robert Kinicki, adapted to C++ and the use of objects by Alexi Kessler
	
	init_mall fills in specific characteristics of all the locations on the First and Second Floors of RoboMall 
*/

#include<stdio.h>
#include "externals.h"


void printType(){
int i,j,k ;
char cell;

 for (k = First; k <= Second; k++)
 {
   printf("      ");
   for (j = MIN; j <= MAX; j++)
     printf("%2d",j);
   
   for (i = MIN; i <= MAX; i++)
   {
     printf("\n %2d   ",i);

     for (j = MIN; j <= MAX; j++)
     {
       if ((Mall[i][j][k]).getType() == INVALID)
	 cell = ' ';
       else
	 cell = 48 + (Mall[i][j][k]).getType();
       printf(" %c", cell);
     }
   }
   printf("\n                %d Floor Types\n\n", k);
 }
 return;
}

/* This print function serves to print out the settings
   of the step array by init_mall. This is useful to make
   sure this property has been set correctly.              */
   
void printStep(){
int i,j,k ;
char cell;

 for (k = First; k <= Second; k++)
 {
   printf("      ");
   for (j = MIN; j <= MAX; j++)
     printf("%2d",j);
   
   for (i = MIN; i <= MAX; i++)
   {
     printf("\n %2d   ",i);

     for (j = MIN; j <= MAX; j++)
     {
       if ((Mall[i][j][k].getStep()) == INVALID)
	 cell = ' ';
       else
	 cell = 48 + (Mall[i][j][k]).getStep();
       printf(" %c", cell);
     }
   }
   printf("\n                %d Floor Steps\n\n", k);
 }
 return;
}

/* init_mall initializes type and step
   based on characteristics of the two floors of RoboMall  */

void init_mall()
{
int i,j,k ;
int dir[8];

// First initialize sparse arrays type and step

 for (k = First; k <= Second; k++)
   for (i = MIN; i <= MAX+1; i++)
   for (j = MIN; j <= MAX+1; j++)

   //  INVALID means the robot should never go here!
   {
       (Mall[i][j][k]).setType(INVALID);
       (Mall[i][j][k]).setStep(INVALID);
	   (Mall[i][j][k]).setRow(i);
	   (Mall[i][j][k]).setCol(j);
	   (Mall[i][j][k]).setFloor(k);
	   
   }

 for (k = First; k <= Second; k++)
 {
   // The directions for the two floors differ
   if (k == First)
   {
     for (i = 0; i <= 7; i++)
       dir[i] = i;
   }
   else
   {
     for (i = 0; i <= 7; i++)
       dir[i] = (i+4)%8;
   }

   for (j = 6; j < 11; j++)
   { 
	 (Mall[MIN][j][k]).setType(One);
	 (Mall[MAX][j][k]).setType(One);
	 (Mall[j][MIN][k]).setType(One);
	 (Mall[j][MAX][k]).setType(One);

     (Mall[MIN][j][k]).setStep(dir[6]);
     (Mall[MAX][j][k]).setStep(dir[2]);
     (Mall[j][MIN][k]).setStep(dir[4]);
     (Mall[j][MAX][k]).setStep(dir[0]);
   }

   for (j = 1; j <= 13; j = j+3)
   {
     for (i = 0; i <= 2; i++)
     {
       (Mall[MID][j+i][k]).setType(One);
       (Mall[j+i][MID][k]).setType(One);

       (Mall[MID][j+i][k]).setStep(dir[2]);
       (Mall[j+i][MID][k]).setStep(dir[4]);
     }
   }

   for (i = 4; i <= 12; i = i+8)
   {
     (Mall[i][4][k]).setType(Store); 
	 (Mall[i][12][k]).setType(Store);
     (Mall[i][6][k]).setType(Store);
	 (Mall[i][10][k]).setType(Store);
     (Mall[6][i][k]).setType(Store);
	 (Mall[10][i][k]).setType(Store);
     (Mall[i][7][k]).setType(TwoWay);
	 (Mall[i] [9][k]).setType(TwoWay);
     (Mall[7][i][k]).setType(TwoWay);
	 (Mall[9][ i][k]).setType(TwoWay);
     (Mall[i][MID][k]).setType(Three);
	 (Mall[MID][i][k]).setType(Three);

     (Mall[i][MID][k]).setStep(dir[4]);
     (Mall[MID][i][k]).setStep(dir[2]);
   }

   (Mall[MID][MID][k]).setStep(dir[2]);
   for (j = 5; j >= 1; j--)
   {
     (Mall[6-j][j][k]).setType(One);
	 (Mall[16-j][10+j][k]).setType(One);

     (Mall[6-j][j][k]).setStep(dir[5]);
     (Mall[16-j][10+j][k]).setStep(dir[1]);
   }
	//bottom left, top right diagonals
   for (i = 1; i <= 5; i++)
   {
     (Mall[i][10+i][k]).setType(One);
	 (Mall[10+i][i][k]).setType(One);

     (Mall[i][10+i][k]).setStep(dir[7]);
     (Mall[10+i][i][k]).setStep(dir[3]);   
   }

   for (i = 3; i <= 13; i = i+10)
    (Mall[i][i][k]).setType(Next);
	(Mall[3][13][k]).setType(Next);
	(Mall[13][3][k]).setType(Next);
	(Mall[MID][MID][k]).setType(Elevator);
 } //end first large for loop
 
// printf("\nInit 2");
 (Mall[MIN][MID][First]).setType(Two);
 (Mall[MID][MIN][First]).setType(Two);
 (Mall[MID][MAX][Second]).setType(Two);
 (Mall[MAX][MID][Second]).setType(Two);

 for (i = 0; i <= 7; i++)
   dir[i] = i;

 for (k = First; k <= Second; k++)
 {
   (Mall[ 4][ 4][k]).setStep(dir[7]);
   (Mall[ 4][12][k]).setStep(dir[1]);
   (Mall[12][ 4][k]).setStep(dir[5]);
   (Mall[12][12][k]).setStep(dir[3]);

   for (j = 4; j <= 12; j = j+8)
   {
     (Mall[ 6][ j][k]).setStep(dir[4]);
	 (Mall[ 7][ j][k]).setStep(dir[4]);
     (Mall[ 9][ j][k]).setStep(dir[0]);
	 (Mall[10][ j][k]).setStep(dir[0]);
     (Mall[ j][ 6][k]).setStep(dir[2]);
	 (Mall[ j][ 7][k]).setStep(dir[2]);
     (Mall[ j][ 9][k]).setStep(dir[6]);
	 (Mall[ j][10][k]).setStep(dir[6]);
   }
 }
 (Mall[MIN][6] [First]).setStep(dir[5]);
 (Mall[10][MAX][Second]).setStep(dir[5]);
 (Mall[10][MIN][First]).setStep(dir[3]);
 (Mall[MIN][10][Second]).setStep(dir[3]);
 (Mall[MAX][10][First]).setStep(dir[1]);
 (Mall[6][MIN][Second]).setStep(dir[1]);
 (Mall[6][MAX][First]).setStep(dir[7]);
 (Mall[MAX][6][Second]).setStep(dir[7]);

 /* These two print functions show that type and step
    are correct.  They can be commented out once program */

 printType();
 printStep();

 return;
}  //end init_mall
