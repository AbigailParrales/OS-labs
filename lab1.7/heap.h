#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

typedef struct node {
    int id;
    int data;
    int b_time;
} node ;

typedef struct maxHeap {
    int size ;
    node *elem ;
} maxHeap ;

node process[10];
int pos_h=0;
float avg_exc_time=0;
int abs_size=0;

/*
    Function to initialize the max heap with size = 0
*/
maxHeap initMaxHeap(int size) {
    maxHeap hp ;
    hp.size = 0 ;
    hp.elem = malloc(size * sizeof(node)) ;
    return hp ;
}


/*
    Function to swap data within two nodes of the max heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a max heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(maxHeap *hp, int i) {
    int largest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data > hp->elem[i].data) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data > hp->elem[largest].data) {
        largest = RCHILD(i) ;
    }
    if(largest != i) {
        swap(&(hp->elem[i]), &(hp->elem[largest])) ;
        heapify(hp, largest) ;
    }
}


/* 
    Build a Max Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMaxHeap() function to build the heap in O(n) time
*/
void buildMaxHeap(maxHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.data = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}


/*
    Function to insert a node into the max heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(maxHeap *hp, int data, int id, int b_time) {
    node nd ;
    nd.data = data ;
    nd.id = id;
    nd.b_time = b_time;

    int i = (hp->size)++ ;
    while(i && nd.data > hp->elem[PARENT(i)].data) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
}


/*
    Function to delete a node from the max heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated

    Returns 1 if Max Heap is empty
*/
int deleteNode(maxHeap *hp) {
    //printf("Size prev delete%d\n\n-----------------------\n",hp->size);

    if(hp->size) {
        process[pos_h]= hp->elem[0];
        printf("Deleting node %d    %d    %d\n\n", hp->elem[0].data,hp->elem[0].id,hp->elem[0].b_time) ;

        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;

        //printf("Size pos_ht delete%d\n\n",hp->size);
        return 0;
    } else {
        printf("\nMax Heap is empty!\n") ;
        //free(hp->elem) ;
        return 1;
    }
}


/*
    Function to get minimum node from a max heap
    The minimum node shall always be one of the leaf nodes. So we shall recursively
    move through both left and right child, until we find their minimum nodes, and
    compare which is smaller. It shall be done recursively until we get the minimum
    node
*/
int getMinNode(maxHeap *hp, int i) {
    if(LCHILD(i) >= hp->size) {
        return hp->elem[i].data ;
    }

    int l = getMinNode(hp, LCHILD(i)) ;
    int r = getMinNode(hp, RCHILD(i)) ;

    if(l <= r) {
        return l ;
    } else {
        return r ;
    }
}

/*
    Function to get maximum node from a max heap	
*/
/*int getMax(maxHeap *hp){
	int max=hp->elem[0].data;
	return max;
}*/
node getMax(maxHeap *hp){
    return hp->elem[0];
}
/*
    Function to clear the memory allocated for the max heap
*/
void deleteMaxHeap(maxHeap *hp) {
    free(hp->elem) ;
}


void inorderTraversal(maxHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("P%d: b_time: %d priority: %d\n", hp->elem[i].id, hp->elem[i].b_time, hp->elem[i].data) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}


void preorderTraversal(maxHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        preorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        preorderTraversal(hp, RCHILD(i)) ;
    }
   printf("P%d: b_time: %d priority: %d\n", hp->elem[i].id, hp->elem[i].b_time, hp->elem[i].data) ;
}


void pos_htorderTraversal(maxHeap *hp, int i) {
  printf("P%d: b_time: %d priority: %d\n", hp->elem[i].id, hp->elem[i].b_time, hp->elem[i].data) ;
    if(LCHILD(i) < hp->size) {
        pos_htorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        pos_htorderTraversal(hp, RCHILD(i)) ;
    }
}


/*
    Function to display all the nodes in the max heap
*/
void levelorderTraversal(maxHeap *hp) {
    int i ;
    printf("Level Order: \n");
    for(i = 0; i < hp->size; i++) {
        printf("P%d: b_time: %d priority: %d\n", hp->elem[i].id, hp->elem[i].b_time, hp->elem[i].data) ;
    }
}

void print_MaxSort(void){
    int i=0;
    printf("Excecuting process: \n");
    for (i; i < abs_size; ++i){
        
        printf("P%d: b_time%d: priority: %d\n", process[i].id, process[i].b_time, process[i].data) ;
    }
    printf("Average excecution time: %.1f\n",avg_exc_time);
}

void MaxSort(maxHeap *hp){
    int i=0;
    abs_size=hp->size;
    
    int exc_time=0;
    
    for (i; i < abs_size; ++i){
        process[i]=hp->elem[0];
        exc_time+=process[i].b_time;
        //printf("P%d: b_time%d: priority%d: \n", process[i].id, process[i].b_time, process[i].data) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        heapify(hp,0);
    }
    avg_exc_time=(float)exc_time/(float)abs_size;
}

void MinSort(maxHeap *hp){
    int i;

    printf("Excecuting process: \n");
    MaxSort(hp);
    i = abs_size-1;
    
    for (i; i>-1 ; --i){
        printf("P%d: b_time: %d priority: %d\n", process[i].id, process[i].data, process[i].b_time) ;
    }
    printf("Average excecution time: %.1f\n",avg_exc_time);
}

void print(maxHeap *hp){
    int i=0;
	for(i; i < hp->size; i++) {
        printf("P%d: b_time: %d priority: %d\n", hp->elem[i].id, hp->elem[i].b_time, hp->elem[i].data) ;
    }
}
