//Handle multiple socket connections with select and fd_set
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
	
#define TRUE 1 
#define FALSE 0 
	
void open_server_socket(int port) 
{ 
	int opt = TRUE; 
	int master_socket, addrlen, new_socket, client_socket[3], max_clients = 3, activity, index, sd, valread;
	int number_of_clients = 0; 
	int max_sd; 

	struct sockaddr_in address; 
		
	char buffer[1025]; //data buffer of 1K 
		
	//set of socket descriptors 
	fd_set readfds; 
		
	//a messages 
	char *wait_msg = "wait_client\n";
	char *start_msg = "start_game\n";
	char *end_msg = "end_game\n";
	char *close_client = "close_client";
	char *answer = "answer";
	
	//initialise all client_socket[] to 0 so not checked 
	for (index = 0; index < max_clients; index++) 
	{ 
		client_socket[index] = 0; 
	} 
		
	//create a master socket 
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	
	//type of socket created 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( port ); 
		
	//bind the socket to localhost port 
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Listener on port %d \n", port); 
		
	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(master_socket, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
		
	//accept the incoming connection 
	addrlen = sizeof(address); 
	puts("Waiting for connections ..."); 
		
	while(TRUE) 
	{ 
		//clear the socket set 
		FD_ZERO(&readfds); 
	
		//add master socket to set 
		FD_SET(master_socket, &readfds); 
		max_sd = master_socket; 
			
		//add child sockets to set 
		for ( index = 0 ; index < max_clients ; index++) 
		{ 
			//socket descriptor 
			sd = client_socket[index]; 
				
			//if valid socket descriptor then add to read list 
			if(sd > 0) 
				FD_SET( sd , &readfds); 
				
			//highest file descriptor number, need it for the select function 
			if(sd > max_sd) 
				max_sd = sd; 
		} 
	
		//wait for an activity on one of the sockets , timeout is NULL , 
		//so wait indefinitely 
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL); 
	
		if ((activity < 0) && (errno!=EINTR)) 
		{ 
			printf("select error"); 
		} 
			
		//If something happened on the master socket , 
		//then its an incoming connection 
		if (FD_ISSET(master_socket, &readfds)) 
		{ 
			if ((new_socket = accept(master_socket, 
					(struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
			{ 
				perror("accept"); 
				exit(EXIT_FAILURE); 
			} 
			
			//inform user of socket number - used in send and receive commands 
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs 
				(address.sin_port)); 
		
			puts("Welcome message sent successfully"); 
				
			//add new socket to array of sockets 
			for (index = 0; index < max_clients; index++) 
			{ 
				//if position is empty 
				if( client_socket[index] == 0 ) 
				{ 
					client_socket[index] = new_socket; 
					printf("Adding to list of sockets as %d\n" , index); 
					number_of_clients++;
						
					break; 
				} 
			} 

			if(number_of_clients == max_clients){
				//send start_game if max number of clients is reached
				for(index = 0; index < max_clients; index++){
					if(send(client_socket[index], start_msg, strlen(start_msg), 0) != strlen(start_msg))
						perror("send");
				}
			}
			else{
				//send wait_msg if max number of clients is not reached
				if( send(new_socket, wait_msg, strlen(wait_msg), 0) != strlen(wait_msg) ) 
				{ 
					perror("send"); 
				}
			}
			
		} 
			
		//Commands handler 
		for (index = 0; index < max_clients; index++) 
		{ 
			sd = client_socket[index]; 
				
			if (FD_ISSET( sd , &readfds)) 
			{ 
				//Check if it was for closing , and also read the 
				//incoming message 
				valread = read( sd , buffer, 1024);
				
				if (valread == 0) 
				{ 
					//Somebody disconnected , get his details and print 
					getpeername(sd , (struct sockaddr*)&address ,(socklen_t*)&addrlen); 
					printf("Host disconnected , ip %s , port %d \n" , 
						inet_ntoa(address.sin_addr) , ntohs(address.sin_port)); 
						
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					client_socket[index] = 0; 
				} 
				//Echo back the message that came in
				else if (strncmp(buffer, close_client, 12) == 0)
				{
					//Somebody disconnected , get his details and print 
					getpeername(sd , (struct sockaddr*)&address ,(socklen_t*)&addrlen); 
					printf("Host disconnected , ip %s , port %d \n" , 
						inet_ntoa(address.sin_addr) , ntohs(address.sin_port)); 
						
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					client_socket[index] = 0;
				}
				else if(strncmp(buffer, answer,6) == 0)
				{ 
					//set the string terminating NULL byte on the end 
					//of the data read 
					char* answer_accept = "answer is accepted\n\n";
					send(sd , answer_accept , strlen(answer_accept) , 0 ); 
				} 
			} 
		} 
	}  
} 

void open_client_socket(int port, char* ip)
{

}
