In this project the objective was learn to use sockets in LINUX.

Requirements:
	-server1.c
	-client1.c

Instructions:
	For compiling:
		gcc server1.c -o server1.o
		gcc client1.c -o client1.o
	
	For running in the same terminal:
		./server1.o &
		./client1.o [operation (+) (-) (x)] [operators separated with symbols]
	
	For running in different terminals:
		[Server-terminal]
		  ./server1.o 
		[Client-terminal]
		  ./client1.o [operation (+) (-) (x)] [operators separated with symbols]
