/**
1. Brynn McGovern
   2370579
   bmcgovern@chapman.edu
   CPSC 380-01
   Assignment 7 - Disk Scheduling
2. A program to simulate different disk scheduling algorithms. Program takes in a file of cylinder
  requests and a starting position. Algorithms demonstrated are FCFS, SSTF, SCAN, and CSCAN.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CYLINDERS 5000
#define REQUESTS 1000

int start = 0;
int requestArray[REQUESTS];


/**
  FCFS()
  @param int* requestArray
  @return int
  Method to simulate First Come First Serve scheduling algorithm.
*/
int FCFS(int* requestArray){

  int headMovement = 0;
  int initial = start;

  for(int i = 0; i < REQUESTS; ++i){
    headMovement += abs(requestArray[i] - initial);
    initial = requestArray[i];
  }

  return headMovement;
}

/**
  SSTF()
  @param int* requestArray
  @return int
  Method to simulate Shortest Seek Time First scheduling algorithm.
*/
int SSTF(int* requestArray){


  int headMovement = 0;
  int initial = start;
  int count = 0;
  int tempArray[REQUESTS];
  for(int i = 0; i < REQUESTS; ++i){
    tempArray[i] = requestArray[i];
  }
  while(count != REQUESTS){
    int min = 4999;
    int d;
    int index;
    for(int i = 0; i < REQUESTS; ++i){
      d = abs(tempArray[i] - initial);
      if(min > d){
        min = d;
        index = i;
      }
    }

    headMovement += min;
    initial = tempArray[index];
    tempArray[index] = 4999;
    count++;
  }


  return headMovement;
}

/**
  SCAN()
  @param int* requestArray
  @return int
  Method to simulate SCAN scheduling algorithm.
*/
int SCAN(int* requestArray){

  int tempQueue[REQUESTS + 5];
  int initial = start;
  int i;
  int j;
  int k;
  int headMovement=0;
  int max = 4999;
  int difference;
  int temp;
  int tempArray1[REQUESTS];
  int tempArray2[REQUESTS];
  int temp1=0;
  int temp2=0;

   for(i=1;i<=REQUESTS;i++)
   {
     temp = requestArray[i -1];

       if(temp>initial)
       {
           tempArray1[temp1]=temp;
           temp1++;
       }
       else
       {
           tempArray2[temp2]=temp;
           temp2++;
       }
   }


   for(i=0;i<temp1-1;i++)
   {
       for(j=i+1;j<temp1;j++)
       {
           if(tempArray1[i]>tempArray1[j])
           {
               temp=tempArray1[i];
               tempArray1[i]=tempArray1[j];
               tempArray1[j]=temp;
           }
       }
   }


   for(i=0;i<temp2-1;i++)
   {
       for(j=i+1;j<temp2;j++)
       {
           if(tempArray2[i]<tempArray2[j])
           {
               temp=tempArray2[i];
               tempArray2[i]=tempArray2[j];
               tempArray2[j]=temp;
           }
       }
   }


   for(i=1,j=0;j<temp1;i++,j++)
   {
       tempQueue[i]=tempArray1[j];
   }

   tempQueue[i]=max;


   for(i=temp1+2,j=0;j<temp2;i++,j++)
   {
       tempQueue[i]=tempArray2[j];
   }


   tempQueue[i]=0;


   tempQueue[0]=initial;



   for(j=0; j<=REQUESTS; j++)
   {

       difference = abs(tempQueue[j+1]-tempQueue[j]);
       headMovement = headMovement + difference;

   }

   return headMovement;
}

/**
  CSCAN()
  @param int* requestArray
  @return int
  Method to simulate CSCAN scheduling algorithm.
*/
int CSCAN(int* requestArray){

  int i;
  int j;
  int headMovement = 0;
  int initial = start;
  int max = 4999;
  int move = 1;

    for (i = 0; i < REQUESTS; i++){
        for (j = 0; j < REQUESTS - i - 1; j++){
            if (requestArray[j] > requestArray[j + 1]){
                int temp;
                temp = requestArray[j];
                requestArray[j] = requestArray[j + 1];
                requestArray[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < REQUESTS; i++){
        if (initial < requestArray[i]){
            index = i;
            break;
        }
    }
    if (move == 1){
        for (i = index; i < REQUESTS; i++){
            headMovement = headMovement + abs(requestArray[i] - initial);
            initial = requestArray[i];
        }
        headMovement = headMovement + abs(max - requestArray[i - 1] - 1);
        headMovement = headMovement + abs(max - 1 - 0);
        initial = 0;
        for (i = 0; i < index; i++){
            headMovement = headMovement + abs(requestArray[i] - initial);
            initial = requestArray[i];
        }
    }
    else{
        for (i = index - 1; i >= 0; i--){
            headMovement = headMovement + abs(requestArray[i] - initial);
            initial = requestArray[i];
        }
        headMovement = headMovement + abs(requestArray[i + 1] - 0);
        headMovement = headMovement + abs(max - 1 - 0);
        initial = max - 1;
        for (i = REQUESTS - 1; i >= index; i--){
            headMovement = headMovement + abs(requestArray[i] - initial);
            initial = requestArray[i];
        }
    }
    return headMovement;
}

int main(int argc, char* argv[]){
  start = atoi(argv[1]);
  char *file = argv[2];
  FILE *cylinders = fopen(file, "r");
  if(argc != 3){
    printf("Program should compile with initial position followed by the file name. ");
    exit(-1);
  }

  for(int i = 0; i < REQUESTS; ++i){
    fscanf(cylinders, "%d", &requestArray[i]);
    //printf("%d\n", requestArray[i]);
  }

  printf("FCFS head movement: %d\n", FCFS(requestArray));
  printf("SSTF head movement: %d\n", SSTF(requestArray));
  printf("SCAN head movement: %d\n", SCAN(requestArray));
  printf("CSCAN head movement: %d\n", CSCAN(requestArray));


}
