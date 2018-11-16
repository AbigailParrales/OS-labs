/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
	char operation;
	int values[10];
	int noElements;
    int result;
} package;

int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }

/*  We can now read/write via sockfd.  */
    package p;
    int i;

    p.noElements=argc-2;

	p.operation = argv[1][0];
    //printf("Client: Operation: %c\n", p.operation);
    if(p.operation=='x'){
        printf("Client: We've entered multiplication option\n");
    }

    for (i=2; i < argc; i++){	//pos1: command, pos2: operation, pos3-posN: operators
      	p.values[i-2]=atoi(argv[i]);
      	printf("Client: Num received: %d\n", p.values[i-2]);
    }

    //printf("No of elements: %d\n", p.noElements);

    write(sockfd, &p, sizeof(p));

    read(sockfd, &p, sizeof(p));
    //read(sockfd, &ch, 1);
    //printf("Client: char from server = %c\n", ch);
    printf("Client: Result: %d\n",p.result);
    close(sockfd);
    exit(0);
}
