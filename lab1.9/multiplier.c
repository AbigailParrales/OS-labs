#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE_LADO  3

long **buffers; // An array of NUM_BUFFERS pointers to the available buffers that will serve as temporal rows to be stored into final result matrix.
long NUM_BUFFERS = 5;      //Número de hilos ejecutándose de una vez


void print_mat(long *mat,int x){
  int i;

   for(i = 0; i<(x); i++){
     printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line
    }
}

/*
Reads matrix file and returns an long type array with content of matrix.
*/   
long* readMatrix(char *filename){    
  long i=0;                                         //index of the matrix

  //creates an array that will be the returned as the matrix readed
  long* mat=malloc((SIZE_LADO*SIZE_LADO)*sizeof(long)); 

  FILE *file;
  file=fopen(filename, "r");

  for(i = 0; i < (SIZE_LADO*SIZE_LADO); i++){
    fscanf(file, "%ld", &mat[i]);
    //printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line
  }


  fclose(file); 
  return mat;
}


void test_threads(){

}

/*
  Returns the specified array that represents a column in the matrix array.
*/
long * getColumn(int col, long *matrix){
  int i;
  long* column = malloc(SIZE_LADO*sizeof(long)); 
  for(i=0;i<SIZE_LADO;i++) {
    column[i]=matrix[(i*SIZE_LADO)+col];
    //printf("i= %d ::: %ld\n",i, column[i]);               //prints the long found in the line
  }
  return column;
}

/*
  Returns the specified array that represents a row in the matrix array.
*/
long * getRow(int row, long *matrix){
  int i;
  long* row_t = malloc(SIZE_LADO*sizeof(long)); 
  for(i=0;i<SIZE_LADO;i++) {
    row_t[i]=matrix[i+(row*SIZE_LADO)];
    //printf("i= %d ::: %ld\n",i, column[i]);               //prints the long found in the line
  }
  return row_t;
}

/*
Given 2 arrays of 2000 lenght, it calculates the dot product and returns it as a long type value.
*/
long dotProduct(long *vec1, long *vec2){
  int i;    //position
  long sum=0;

  for(i=0;i<SIZE_LADO;i++) {
    sum=((vec1[i])*(vec2[i]))+sum;
    //printf("%d * %d = %d\n",vec1[i],vec2[i],sum);
  }
  return sum;
}

/*
Here's where all the magic happens. Explained in Matrix multiplication section
*/
void multiply(long *matA, long *matB){
// long * multiply(long *matA, long *matB){
  int row,column,i;
  long* row_tmp;
  long* mult = malloc(SIZE_LADO*sizeof(long)); 
  long**mat = malloc(SIZE_LADO*sizeof(long)); 

  for(row=0;row<SIZE_LADO;row++) {
    row_tmp=getRow(row,matA);

    for(column=0;column<SIZE_LADO;column++) {
      mult[column]=dotProduct(row_tmp,getColumn(column,matB));
    }

    mat[row]=mult;
    print_mat(mat[row],SIZE_LADO);
  }


  // return mult;
}

int main(){
    //print_mat_a(readMatrix_a("matA.dat"));
    //readMatrix("matA.dat");
    //getColumn(1,readMatrix("tst.dat"));
    // print_mat(getColumn(1,readMatrix("tst.dat")),SIZE_LADO);
    // print_mat(getRow(1,readMatrix("tst.dat")),SIZE_LADO);
    //print_mat(multiply(getRow(1,readMatrix("tst.dat")),getColumn(1,readMatrix("tst.dat"))),SIZE_LADO);

    long* A = getRow(0,readMatrix("tst.dat"));
    long* B = getColumn(0,readMatrix("tst.dat"));
    // printf("%d\n",dotProduct(A,B));

    multiply(readMatrix("tst.dat"),readMatrix("tst.dat"));
}
