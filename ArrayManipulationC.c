/*
 ============================================================================
 Name        : ArrayManipulationC.c
 Author      : ax
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	false =0,
	true =1
} BOOL ;

typedef int (*FUNP) (float*, float);

float * initialArrayP = NULL;
float * ArrayP = NULL;
int ArraySize = -1;
BOOL isElementSet = false;

float FindMixMax(float * Array ,int Mx)
{
	int i;
	float res;

	if (Array == NULL || ArraySize ==-1 ) return 2;

	res = Array[0];

	for (i = 0 ; i <ArraySize ; i ++ )
	{
		if (Mx == -1)
		{
			res = (res > Array[i])? Array[i]:res;

		}
		else if (Mx == 1)
		{
			res = (res < Array[i])? Array[i]:res;
		}

	}

	return res;

}


int InitialArray( float * Array, float size);
int CreateArrayElements( float * Array, float elem);
int SortArray(float * Array, float dir);
int FindEleminArray(float * Array, float tar);
int PrintArray(float * Array, float size);
int ReversPrintArray(float* Array, float size);
int PrintArrayStatistics(float *Array, float size);
int ResetArray(float * Array, float size);


FUNP fp[]={
		InitialArray,
		CreateArrayElements,
		SortArray,
		FindEleminArray,
		PrintArray,
		ReversPrintArray,
		PrintArrayStatistics,
		ResetArray
};
int InitialArray (float *Array, float size)
{
   if (size <= 0)
   {
	   return -3;
   }
   else
   {
	   initialArrayP = malloc( sizeof(float) * size);
	   if (initialArrayP != NULL) return -3;
	   ArraySize = size;

   }

   return 0;
}

int CreateArrayElements( float * Array, float elem)
{
    int i;
    float el;
	if (ArraySize <=  0 || Array == NULL)
	{

		printf("Your array is not initialized yet!\n");
		return -3;
	}
	else
	{
	   for (i = 0; i < ArraySize; i ++)
	   {
          printf("Enter array element %d:", i);
          scanf("%f",&el);
          Array[i]=el;
	   }
	}

	ArrayP = malloc( sizeof(float) * ArraySize);

	memcpy(ArrayP, initialArrayP, ArraySize*sizeof(float) );

	isElementSet = true;
    return 1;
}


int partition(float *Array, int ld, int rd, int dir)
{

	float pivot = Array[ld];

	while (ld < rd)
	{
      if(dir == -1)
      {
    	  while ( ld < rd && Array[rd] > pivot)  rd--;
      }
      else if (dir == 1)
      {
    	  while ( ld < rd && Array[rd] < pivot)  rd--;
      }
      if (ld < rd) Array[ld++]= Array[rd];

      if (dir == -1)
      {
    	  while (ld < rd && Array[ld] < pivot) ld++;
      }
      else if (dir ==1)
      {
    	  while (ld < rd && Array[ld] > pivot) ld++;
      }
      if (ld < rd) Array[rd--]=Array[ld];

	}

	Array[ld] = pivot;

	return ld;



}



void sortQuick(float * Array, int ld, int rd ,int dir)
{

  int pivotPos;

  if (ld < rd)
  {
	  pivotPos = partition(Array, ld, rd , dir);
	  sortQuick(Array, ld, pivotPos-1,dir);
	  sortQuick(Array, pivotPos+1, rd, dir);

  }

}


int SortArray(float * Array, float dir)
{
	if (Array == NULL || isElementSet == false)
	{
		printf("Your array is not initialized yet!\n");
		return -3;
	}
	if (dir == -1)
	{
       sortQuick( Array , 0, ArraySize-1 , -1);
	}
	else if (dir == 1)
	{
	   sortQuick(Array , 0, ArraySize-1 , 1 );
	}

	return 1;

}

int FindEleminArray(float * Array, float tar)
{
	int i=0 ;
	if(Array == NULL || ArraySize == -1  || isElementSet == false )
	{
		printf("Your array is not initialized yet!\n");
		return -3;
	}

	while (i < ArraySize )
	{
		if (Array[i] ==  tar) return i+1;
		i++;
	}
    return -1;
}


int PrintArray(float * Array, float size)
{
	int i;

	if (Array == NULL || size <= 0  || isElementSet == false )
	{
		printf("Your array is not initialized yet!\n");
		return 2;
	}

	for (i =0 ; i < size ; i ++)
	{
		printf("%3g ", Array[i]);

	}
	printf("\n");
    return 1;

}


int ReversPrintArray(float* Array, float size)
{
   int i;

   if (Array == NULL || size <= 0 || isElementSet == false)
	{
	   printf("Your array is not initialized yet!\n");
	   return -3;
	}

   for (i = size-1; i > -1 ; i --)
   {
	   printf("%3g", Array[i]);

   }

   printf("\n");
   return 1;
}





int PrintArrayStatistics(float *Array, float size)
{
  float Max, Min, Total, Average;

  int i=0;

  if (Array == NULL || size <=0 || isElementSet == false )
  {
	  printf("Your array is not initialized yet!\n");
	  return -3;
  }


  Min = FindMixMax( Array, -1);
  Max = FindMixMax( Array, 1);

  while (i < size )
  {
	  Total += Array[i];
      i++;
  }

  Average =  Total/size;

  printf ("Min: %3g\n", Min);
  printf ("Man: %3g\n", Max);
  printf ("Total: %3g\n", Total);
  printf ("Average: %3g\n", Average);

  return 1;

}

int ResetArray(float * Array, float size)
{
	if(Array == NULL || size <= 0 || isElementSet == false)
	{
	    printf("Your array is not initialized yet!\n");
		return -3;
	}

	memcpy(Array, initialArrayP, size*sizeof(float) );
	return 1;
}


void ScreenPrint(void)
{
	printf("\n");
	printf("1- Enter the size of the array\n");
	printf("2- Enter the array element\n");
	printf("3- Sort the array\n");
	printf("4- Find a number within the array\n");
	printf("5- Print the array\n");
	printf("6- Reverse print the array\n");
	printf("7- print array statistics (min, max, average, total)\n");
	printf("8- Rest the array to original\n");
	printf("9- Quit\n");
}


int main(void) {

	BOOL isLoop = true;
	BOOL isRepeat = true;
    char Dir[46]={};
	char choose[50]={};
	float target;
	int res;
	// go around eclipse Console out put bug
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	while (isLoop)
	{
		ScreenPrint();
		printf("\nPlease enter your choice:");
		scanf("%s",choose);

		if (  choose[0] > '9' ||  choose[0] < '1' || choose[1] != '\0')
			{
				printf("That's not a valid choice\n");
				continue;
			}

		   switch (choose[0])
		   {
		   case '1':
			   printf("What is the size of you array (1 -20)? ");
			   scanf("%d", &ArraySize);
			   if (ArraySize < 1 || ArraySize> 20 )
			   {
				   printf("Array size should be between 1 and 20\n");
				   ArraySize = -1;
			   }
			   else
			   {
				   printf("Array size set\n");
				   fp[1-1](NULL, ArraySize );
			   }

			break;
		   case '2':
			   fp[2-1](initialArrayP, ArraySize);
			break;
		   case '3':
				if(ArrayP == NULL || ArraySize <= 0 || isElementSet == false)
				{
				    printf("Your array is not initialized yet!\n");
				    break;
				}
				isRepeat = true;
			   do
			   {
				   printf("Please choose Ascending/Descending (A/D)?");

				   scanf("%s", Dir);

				   if ((Dir[0] == 'D' && Dir[1] == '\0' ) || (Dir[0] == 'A' && Dir[1] == '\0'))
				   {
					   if (Dir[0] == 'D')
					   {
						 printf("Array sorted (Descending)\n");

						 fp[3-1](ArrayP, 1);
					   }
					   else if (Dir[0] == 'A')
					   {
						 printf("Array sorted (Ascending)\n");
						 fp[3-1](ArrayP, -1);
					   }

					   fp[4](ArrayP, ArraySize);

					   isRepeat = false;

					   continue;

				   }
				   else
				   {
					   printf("That's not a valid choice\n");
				   }
			   }while(isRepeat);

			break;
		   case '4':

				  printf("Please enter a number to be searched in the array:");

				  scanf("%f", &target);
				  res=fp[4-1](ArrayP, target);

				  if (res == -1)
				  {
					  printf ("%3g was not found in the array!\n" , target);
				  }
				  else
				  {
                      printf("%3g was found at the position [%d] in the array", target ,res);
				  }


			break;
		   case '5':
			   fp[5-1](ArrayP, ArraySize);
			break;
		   case '6':
			   fp[6-1](ArrayP, ArraySize);
			break;
		   case '7':
			   fp[7-1](ArrayP, ArraySize);
			break;
		   case '8':
			   fp[8-1](ArrayP, ArraySize);
			break;
		   case '9':
			   isLoop = false;
			break;
		   default:
			 printf("That's not a valid choice\n");

			break;
		   }


	}



}
