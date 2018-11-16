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

int main()
{
    int result;
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;
        result=0;
        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

/*  We can now read/write to client on client_sockfd.  */

        package p;

        read(client_sockfd, &p, sizeof(p));

        printf("Server: No of elements: %d\n", p.noElements);
        printf("Server: Operation: %c\n", p.operation);
        int pos;
        int result;

        if(p.operation=='+'){
            result=p.values[0];
            for(pos=1; pos<p.noElements; pos++){
                result+=p.values[pos];
                printf("Server: Operation: %d -- tmp_result: %d\n",pos,result);
            }
        }

        else if(p.operation=='-'){
            result=p.values[0];
            for(pos=1; pos<p.noElements; pos++){
                result-=p.values[pos];
                printf("Server: Operation: %d -- tmp_result: %d\n",pos,result);
            }
        }

        else if(p.operation=='x'){
            result=p.values[0];
            for(pos=1; pos<p.noElements; pos++){
                result*=p.values[pos];
                //printf("Server: Operation: %d -- tmp_result: %d\n",pos,result);
            }
        }

        else{
            result=-99999;
        }

        p.result=result;

        int i;
        for (i=0; i < p.noElements; i++){   //pos1: command, pos2: operation, pos3-posN: operators
            printf("Server: Num received: %d\n", p.values[i]);
        }

        printf("Server: Result: %d\n",p.result);

        ch++;
        write(client_sockfd, &p, sizeof(p));
        close(client_sockfd);
    }
}

