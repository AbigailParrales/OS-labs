#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

long NUM_BUFFERS = 5;      //Número de hilos ejecutándose de una vez

/*void print_mat(long *mat){
  int i,j;

   for(i = 0; i < 2000; i++){
    for(j = 0; j < 4; j++){
      printf("%ld\n",mat[i][j]); //Use lf for longs
    }
}*/

/*
Reads matrix file and returns an long type array with content of matrix.
 */
void readMatrix(char *filename){    
//long * readMatrix(char *filename){    
  long i;
  long j;

  /*matrix*/
  /*Use double , you have floating numbers not long*/

 long** mat=malloc(4000000*sizeof(long*)); 
  //long** mat=malloc(4000000*sizeof(long*)); 

  for(i=0;i<4000000;++i)
    mat[i]=malloc(4*sizeof(long));


  FILE *file;
  file=fopen(filename, "r");

  for(i = 0; i < 2000; i++){
    for(j = 0; j < 4; j++){
      //Use ld for longs
      if (!fscanf(file, "%ld", &mat[i][j])) 
        break;
      // mat[i][j] -= '0'; 
      printf("%ld\n",mat[i][j]); //Use lf for longs
    }

  }
  fclose(file);
  //returns *mat;
}

/*void test_threads(){

}*/


int main(){
    //print_mat(readMatrix("matA.dat"));
    readMatrix("matA.dat");
}
