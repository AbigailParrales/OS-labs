#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE_LADO  3

long **buffers;             // An array of NUM_BUFFERS pointers to the available buffers that will serve as temporal rows to be stored into final result matrix.
long NUM_BUFFERS = 5;       //Número de hilos ejecutándose de una vez
pthread_mutex_t *mutexes;   // Mutexes that will help to know which buffer is available
long * result;
long *matB, *matA;


typedef struct {
    int row;
    int column;
} coordinates;

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
Search for an available buffer, if so it returns the available lock id which is the same buffer id, otherwise returns -1
*/
int getLock(){
  int i;
  for(i=0; i<NUM_BUFFERS; i++){
    if(pthread_mutex_trylock(&mutexes[i])==0){
      return i;
    }
  }
  return -1;
}

/*
Releases a buffer and unlock the mutex. Returns 0 for successful unlock, otherwise -1.
*/
int releaseLock(int lock){
  if((pthread_mutex_unlock(&mutexes[lock]))==0){
    return 0;
  } 
  else {
    return -1;  
  }
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


void *mult(coordinates *parameters) 
{
    int status;
    long * column;
    long * row;
    row = getRow(parameters->row, matA);
    do {
        status = getLock();
    } while(status < 0);
    

}

long *multiply(long *matA, long *matB){   
    int i;
    int j;
    long * result;
    pthread_t tid [SIZE_LADO];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    coordinates args;
    for (i = 0; i < SIZE_LADO; i++){
        for (j = 0; j < SIZE_LADO; j++){
            args.row = j;
            args.column = i;
            pthread_create(&tid[i],&attr,mult,(void *)&args);
            printf("j= %d ::: %ld\n",i, result[j]);               //prints the long found in the line
        }
    }
    return result;
}



/*
Here's where all the magic happens. Explained in Matrix multiplication section
*/
/*void multiply(long *matA, long *matB){
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
}*/

int saveResultMatrix(long *result)
{
    FILE *file;
    file = fopen("result.data", "w");
    int i;
    if (file == NULL || file == NULL) 
    {   
        printf("Error! Could not open file\n"); 
        return -1;
    }
    for (i = 0 ; i < SIZE_LADO ; i++)
    {
        fprintf(file, "%d\n", result[i]);
    }
    return 0;
}

int main(){
    //print_mat_a(readMatrix_a("matA.dat"));
    //readMatrix("matA.dat");
    //getColumn(1,readMatrix("tst.dat"));
    // print_mat(getColumn(1,readMatrix("tst.dat")),SIZE_LADO);
    // print_mat(getRow(1,readMatrix("tst.dat")),SIZE_LADO);
    //print_mat(multiply(getRow(1,readMatrix("tst.dat")),getColumn(1,readMatrix("tst.dat"))),SIZE_LADO);

    // long* A = getRow(0,readMatrix("tst.dat"));
    // long* B = getColumn(0,readMatrix("tst.dat"));
    // printf("%d\n",dotProduct(A,B));

    //multiply(readMatrix("tst.dat"),readMatrix("tst.dat"));


    // int i;
    // if(argc==2)
    //     NUM_BUFFERS = (int)argv[1];

    //NUM_BUFFERS = (int)argv[1];


    buffers = malloc(NUM_BUFFERS*sizeof(long*)) ;
    mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t)); 
    matA = readMatrix("tst.dat");
    matB = readMatrix("tst.dat");
    result = multiply(matA, matB);
    // print_mat(result,SIZE_LADO);

    if (saveResultMatrix(result)<0)
        printf("file failed!");
}
