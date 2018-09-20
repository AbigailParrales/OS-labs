#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
//void readMatrix_a(char *filename){    
long* readMatrix(char *filename){    
  long i=0;                                         //index of the matrix

  //creates an array that will be the returned as the matrix readed
  long* mat=malloc(9*sizeof(long)); 
  //long* mat=malloc(4000000*sizeof(long)); 

  FILE *file;
  file=fopen(filename, "r");

  for(i = 0; i < 9; i++){
  //for(i = 0; i < 4000000; i++){
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
//void getColumn(int col, long *matrix){
long * getColumn(int col, long *matrix){
  int i;
  long* column = malloc(3*sizeof(long)); 
  //long* column = malloc(2000*sizeof(long)); 

  // for(i=0;i<2000;i++) {
  //   column[i]=matrix[i+(col*2000)];
  //   printf("i= %d ::: %ld\n",i, column[i]);               //prints the long found in the line
  // }

  //testing
  for(i=0;i<3;i++) {
    column[i]=matrix[i+(col*3)];
    //printf("i= %d ::: %ld\n",i, column[i]);               //prints the long found in the line
  }
  return column;
}


int main(){
    //print_mat_a(readMatrix_a("matA.dat"));
    //readMatrix("matA.dat");
    //getColumn(1,readMatrix("tst.dat"));
    print_mat(getColumn(1,readMatrix("tst.dat")),3);

}
