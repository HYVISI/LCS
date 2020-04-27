#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

void GenSeq(char* s, int n);
const int num_alphabet = 5;
void PrintSeq(char* s, int n);
int LCS(char* X, char* Y, int i, int j);
int LCS_Length(char* X, char* Y, int i, int j);
int** c;
int** b; // 0: '↖', -1: '↑', 1: '←'
void PRINT_LCS(char* X, int i, int j);
int FindMax(int a, int b);
void PRINT_ALL_LCSs(char* X,char* Y,char *s, int i, int j,int result);
int GetCurrentUsec();
char *s;

int count=0;
int index1=0;
int main(void) { 
  int i = 10; // length of X
  int j = 10; // length of Y

  char* X, * Y; // sequences
  X = (char*)malloc(sizeof(char)*i);
  Y = (char*)malloc(sizeof(char)*j);

  c = (int**)malloc(sizeof(int*)*(i+1));
  for (int k=0; k<i+1; k++) c[k] = (int*)malloc(sizeof(int)*(j+1));
  b = (int**)malloc(sizeof(int*)*(i+1));
  for (int k=0; k<i+1; k++) b[k] = (int*)malloc(sizeof(int)*(j+1));
  s= (char*)malloc(sizeof(char)*(i+1));
  
  
  

  srand(time(NULL));
  GenSeq(X, i);
  GenSeq(Y, j);
  //X="BDCABA";
  //Y="ABCBDAB";
  
  PrintSeq(X, i);
  PrintSeq(Y, j);

  int t1, t2, result;

  // Divide and Conquer
  t1 = GetCurrentUsec();
  result = LCS(X, Y, i, j);
  t2 = GetCurrentUsec();
  printf("Then length of LCS is %d.\n", result);
  printf("Divide and Conqure took %d usec.\n", t2-t1);

  // Dynaic Programming
  t1 = GetCurrentUsec();
  result = LCS_Length(X, Y, i, j);
  s[result+1]='\0';

  t2 = GetCurrentUsec();
  printf("Then length of LCS is %d.\n", result);
  printf("Dynamic Programming took %d usec.\n", t2-t1);
  
  printf("<");
  PRINT_LCS(X, i, j);
  printf(">\n");
  printf("-----------------All LCS-----------------\n");
  PRINT_ALL_LCSs(X,Y,s,i,j,result-1);
  
 
  


  
  
  // additional point: see the assignment description
  // PRINT_ALL_LCSs(/* define this function in your way*/);

  return 0;
}

//////////////////////////////
//  write your answer below //
//////////////////////////////
/*

for i = 2, j = 2
Divide and Conquer took : [0.33] usec.
Dynamic Programming took : [0.33] usec.

for i = 5, j = 5
Divide and Conquer took : [2.67] usec.
Dynamic Programming took : [1.33] usec.

for i = 10, j = 10
Divide and Conquer took : [402] usec.
Dynamic Programming took : [2.33] usec.

for i = 15, j = 15
Divide and Conquer took : [31491.33] usec.
Dynamic Programming took : [5.67] usec.

*/
//////////////////////////////


int LCS(char* X, char* Y, int i, int j)
{
  int c;
  if ((i==0) || (j==0))
    c = 0;
  else if (X[i-1] == Y[j-1])
    c = LCS(X, Y, i-1, j-1) + 1;
  else
    c = FindMax(LCS(X, Y, i-1, j), LCS(X, Y, i, j-1));
  return c;
}

int FindMax(int a, int b)
{
  if (a >= b) 
    return a;
  else
    return b;
}

int LCS_Length(char* X, char* Y, int i, int j)
{
  for (int k=0; k<i+1; k++) c[i][0] = 0;
  for (int k=0; k<j+1; k++) c[0][j] = 0;
  for (int k=1;k<=i;k++){
    for (int l=1;l<=j;l++){
      if(X[k-1]==Y[l-1]){
        c[k][l]=c[k-1][l-1]+1;
        b[k][l]=0;
      }
      else if(c[k-1][l]>=c[k][l-1]){
        c[k][l]=c[k-1][l];
        b[k][l]=-1;
      }
      else{
        c[k][l]=c[k][l-1];
        b[k][l]=1;
      }
    }
  }
  // implement your code here

  return c[i][j];
}

void PRINT_ALL_LCSs(char *X,char *Y,char *s,int i,int j,int result){

  if(i==0 || j ==0){
        printf("<");
        for(int k=0;k<strlen(s);k++){
          printf("%c, ",s[k]);
        }
        printf(">");
      //temp2[index1]=s;
      //printf("%s,%d",temp[index1],index1);
      index1++;
    printf("\n");
    count++;
    return;
  }

  if(b[i][j]==0){
    s[result]=X[i-1];
    PRINT_ALL_LCSs(X,Y,s,i-1,j-1,result-1);
    //printf("%c, ", X[i-1]);
    return;
  }
  else{
    if(c[i-1][j]==c[i][j-1]){
        PRINT_ALL_LCSs(X,Y,s,i-1,j,result);

        PRINT_ALL_LCSs(X,Y,s,i,j-1,result);
  
        return;
    }
    else{
      if(c[i-1][j]>c[i][j-1]){
        PRINT_ALL_LCSs(X,Y,s,i-1,j,result);
        return;
      }
      else if(c[i-1][j]<c[i][j-1]){
        PRINT_ALL_LCSs(X,Y,s,i,j-1,result);
        return;
      }
      
    }
  }
  return;
}

void PRINT_LCS(char* X, int i, int j)
{
  if ((i==0) || (j==0)){
    return;
  }
  if (b[i][j] == 0)
  {
    PRINT_LCS(X, i-1, j-1);
    printf("%c, ", X[i-1]);
  }
  else if (b[i][j] == -1)
    PRINT_LCS(X, i-1, j);
  else if (b[i][j] == 1)
    PRINT_LCS(X, i, j-1);
    
}

int GetCurrentUsec()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_usec;
}

void GenSeq(char* s, int n)
{
  for (int i=0; i<n; i++)
  {
    s[i] = (char)((random() % num_alphabet)+ 'A');
  }
  return;
}

void PrintSeq(char* s, int n)
{
  printf("<");
  for (int i=0; i<n; i++)
  {
    printf("%c, ", s[i]);
  }
  printf(">\n");
}

