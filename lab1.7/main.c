#include <stdio.h>
#include <string.h>

#include "heap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//FCFS
#define process_no 10

/*rr
*/
#define process_no_RR 10
#define time_out	5

struct process{
		int priority;
		int b_time;
		int ID;
}processes[process_no];

struct process_RR{
		int priority;
		int b_time;
		int ID;

		int b_time_left;
		int finished;
}processes_RR[process_no];

int pos_RR=0;
int process_finished_RR=0;

int pos=0;

void add(int id, int time, int priority){
	processes[pos].ID=id;
	processes[pos].b_time=time;
	processes[pos].priority=priority;
	pos++;
}

void print_fcfs(void){
	int i = 0;
	for (i; i < pos; ++i){
		printf("P%d: b_time= %d, priority= %d \n",processes[i].ID,processes[i].b_time,processes[i].priority);
	}
}

void fcfs(void	){
	int tmp_pNo;

	int tmp_bTime;
	int tmp_priority;

	int exc_time=0;
	float avg_exc_time=0;

	printf("Please enter the number of process you want to to\n");
	scanf("%d", &tmp_pNo);
	
	int i = 0;
	for (i; i < tmp_pNo; ++i){
		printf("Please enter the burst time of the process P%d\n",(i+1));
		scanf("%d", &tmp_bTime);

		printf("Please enter the priority of the process P%d\n",(i+1));
		scanf("%d", &tmp_priority);

		add((i+1), tmp_bTime, tmp_priority);
		exc_time+=tmp_bTime;
	}
	avg_exc_time=(float)exc_time/(float)tmp_pNo;

	print_fcfs();
	printf("Average execution time: %.1f\n", avg_exc_time);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//SJF
void sjf(){
	srand(time(NULL));

	maxHeap h = initMaxHeap(10);

	int tmp_pNo;

	int tmp_bTime;
	int tmp_priority;

	printf("Please enter the number of process you want to to\n");
	scanf("%d", &tmp_pNo);
	
	//process p = init(tmp_pNo);
	int i = 0;
	for (i; i < tmp_pNo; ++i){
		
		printf("Please enter the burst time of the process P%d\n",(i+1));
		scanf("%d", &tmp_bTime);
		
		printf("Please enter the priority of the process P%d\n",(i+1));
		scanf("%d", &tmp_priority);
		insertNode(&h,tmp_bTime,(i+1),tmp_priority);	
		//printf("i: %d\n", i);
		//insertNode(h,rand()%100,(i+1));
	}

/*	insertNode(h,rand()%100,1);			//insert 1
	insertNode(h,rand()%100,2);			//insert 2
	insertNode(h,rand()%100,3);			//insert 3
	insertNode(h,rand()%100,4);			//insert 4
	insertNode(h,rand()%100,5);			//insert 5
	insertNode(h,rand()%100,6);			//insert 6
	insertNode(h,rand()%100,7);			//insert 7
	insertNode(h,rand()%100,8);			//insert 8
	insertNode(h,rand()%100,9);			//insert 9
	insertNode(h,rand()%100,10);		//insert 10
*/

	MinSort(&h);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//priority
void priority(void){
	srand(time(NULL));

	maxHeap h = initMaxHeap(10);

	int tmp_pNo;

	int tmp_bTime;
	int tmp_priority;

	printf("Please enter the number of process you want to to\n");
	scanf("%d", &tmp_pNo);
	
	//process p = init(tmp_pNo);
	int i = 0;
	for (i; i < tmp_pNo; ++i){
		
		printf("Please enter the burst time of the process P%d\n",(i+1));
		scanf("%d", &tmp_bTime);
		
		printf("Please enter the priority of the process P%d\n",(i+1));
		scanf("%d", &tmp_priority);
		insertNode(&h,tmp_priority,(i+1),tmp_bTime);	
		//printf("i: %d\n", i);
		//insertNode(h,rand()%100,(i+1));
	}

/*	insertNode(h,rand()%100,1);			//insert 1
	insertNode(h,rand()%100,2);			//insert 2
	insertNode(h,rand()%100,3);			//insert 3
	insertNode(h,rand()%100,4);			//insert 4
	insertNode(h,rand()%100,5);			//insert 5
	insertNode(h,rand()%100,6);			//insert 6
	insertNode(h,rand()%100,7);			//insert 7
	insertNode(h,rand()%100,8);			//insert 8
	insertNode(h,rand()%100,9);			//insert 9
	insertNode(h,rand()%100,10);		//insert 10
*/

	MaxSort(&h);
	print_MaxSort();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//rr
void add_RR(int id, int time, int priority){
	processes_RR[pos_RR].ID=id;
	processes_RR[pos_RR].b_time=time;
	processes_RR[pos_RR].priority=priority;

	processes_RR[pos_RR].b_time_left=0;
	processes_RR[pos_RR].finished=0;
	pos_RR++;
}

void print_rr(void){
	int i = 0;
	for (i; i < pos_RR; ++i){
		printf("----P%d: priority= %d, b_time= %d, b_time_left= %d, finished= %d----\n",processes_RR[i].ID,processes_RR[i].priority,processes_RR[i].b_time,processes_RR[i].b_time_left, processes_RR[i].finished);
		//printf("P%d: b_time= %d, priority= %d \n",processes_RR[i].ID,processes_RR[i].b_time,processes_RR[i].priority);
	}
}

void rr(void){
	int i=0;
	int cnt=0;

	//while(cnt<10){
	while(process_finished_RR<(pos_RR)){
		/*printf("i: %d\n", i);
		printf("pos_RR %d\n", pos_RR);
		printf("finished processes_RR %d\n", process_finished);

		printf("Ececuting process %d\n", processes_RR[i].ID);

		printf("----P%d: priority= %d, b_time= %d, b_time_left= %d, finished= %d----\n",processes_RR[i].ID,processes_RR[i].priority,processes_RR[i].b_time,processes_RR[i].b_time_left, processes_RR[i].finished);
		
		*/

		if(processes_RR[i].finished==0){				//unfinished
			if(cnt==0||cnt==1){
				processes_RR[i].b_time_left=processes_RR[i].b_time-time_out;
			}
			else{
				processes_RR[i].b_time_left=processes_RR[i].b_time_left-time_out;
			}

			//printf("time left: %d\n", processes_RR[i].b_time_left);
			if(processes_RR[i].b_time_left<=0){		//finish process
				processes_RR[i].b_time_left=0;
				processes_RR[i].finished=1;
				printf("P%d: priority= %d, b_time= %d, b_time_left= %d, finished= %d\n",processes_RR[i].ID,processes_RR[i].priority,processes_RR[i].b_time,processes_RR[i].b_time_left, processes_RR[i].finished);				
				printf("P%d: --> FINISHED!!! \n",processes_RR[i].ID);				
				process_finished_RR++;
			}
			else if(processes_RR[i].b_time_left>0){	//continue executing
				//printf("continue executing P%d\n", processes_RR[i].ID);
				printf("P%d: priority= %d, b_time= %d, b_time_left= %d, finished= %d\n",processes_RR[i].ID,processes_RR[i].priority,processes_RR[i].b_time,processes_RR[i].b_time_left, processes_RR[i].finished);
			}
		}

		else if(processes_RR[i].finished==1){			//finished
			/*printf("P%d: --> Already FINISHED!!! \n",processes_RR[i].ID);
			printf("----P%d: priority= %d, b_time= %d, b_time_left= %d, finished= %d----\n",processes_RR[i].ID,processes_RR[i].priority,processes_RR[i].b_time,processes_RR[i].b_time_left, processes_RR[i].finished);
			*/
		}
		i=((++i)%(pos_RR));
		cnt++;
		//i=((i++)%(pos_RR+1));
	}
}

void rr_stuff(void){
	srand(time(NULL));
	int tmp_pNo;

	int tmp_bTime;
	int tmp_priority;

	int exc_time=0;
	float avg_exc_time=0;

	printf("Please enter the number of process you want to to\n");
	scanf("%d", &tmp_pNo);
	
	int i = 0;
	for (i; i < tmp_pNo; ++i){
		printf("Please enter the burst time of the process P%d\n",(i+1));
		scanf("%d", &tmp_bTime);

		printf("Please enter the priority of the process P%d\n",(i+1));
		scanf("%d", &tmp_priority);
		
		add((i+1), tmp_bTime, tmp_priority);
		exc_time+=tmp_bTime;	
		
		/*
		tmp_bTime=rand()%20;
		add((i+1), tmp_bTime, rand()%10);
		exc_time+=tmp_bTime;*/
	}
	avg_exc_time=(float)exc_time/(float)tmp_pNo;

	//print_rr();
	rr();

	printf("Average execution time: %.1f\n", avg_exc_time);
}


int main(void){
	int tmp_alg;

	while(1){

		printf("Please enter the number of the algorithm you want to to implement\n");
		printf("1.-    fcfs\n");
		printf("2.-    priority\n");
		printf("3.-    sjf\n");
		printf("4.-    rr\n");
		scanf("%d", &tmp_alg);

		if(tmp_alg==1){
			fcfs();
		}
		else if(tmp_alg==2){
			priority();
		}
		else if(tmp_alg==3){
			sjf();
		}
		else if(tmp_alg==4){
			rr_stuff();
		}
	}

	return 0;
}