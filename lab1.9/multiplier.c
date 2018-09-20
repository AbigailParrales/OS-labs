#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

long NUM_BUFFERS = 5;      //Número de hilos ejecutándose de una vez

/* void print_mat(long *mat){
  int i,j;

   for(i = 0; i < 2000; i++){
    for(j = 0; j < 4; j++){
      printf("%ld\n",mat[i][j]); //Use lf for longs
    }
}*/

/*
Reads matrix file and returns an long type array with content of matrix.
 */
void readMatrix_b(char *filename){    
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

/*
Reads matrix file and returns an long type array with content of matrix.
 */
void readMatrix_a(char *filename){    
//long* readMatrix_a(char *filename){    
  long i=0;   //index of the matrix

  //creates an array that will be the returned as the matrix readed
  long* mat=malloc(4000000*sizeof(long)); 
  
  //initialize the matrix
  /*for(i=0;i<4000000;++i)
    *mat=&malloc(sizeof(long));
  */
  //read the file given by filename string
  FILE *file;
  file=fopen(filename, "r");

  //testing...
  // fscanf(file, "%ld", &mat[i]);
  // printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line
  // i++;
  // fscanf(file, "%ld", &mat[i]);
  // printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line

  for(i = 0; i < 4000000; i++){
    fscanf(file, "%ld", &mat[i]);
    printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line
  }

 /* for(i = 0; i < 10; i++){
    //for(j = 0; j < 4; j++){
      //Use ld for longs
      if (!fscanf(file, "%ld", mat[i]))     //checks that the file is't empty
        printf("El archivo está vacio\n");
        break;                              //In such case it breaks
      printf("i= %d ::: %ld\n",i, mat[i]);               //prints the long found in the line
    //}
  }*/

  fclose(file);
  //returns *mat;
}


void test_threads(){

}


int main(){
    //print_mat(readMatrix("matA.dat"));
    readMatrix_a("matA.dat");
}
