#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close() */
#include <errno.h>
#include <string.h> /* memset() */
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define BUFLEN 100
#define PORT "6187"
void err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in my_addr, cli_addr,sin,serv_addr;
    int sockfd, i, n, length; 
    socklen_t slen=sizeof(cli_addr),slen1;
    char buf[BUFLEN], line[BUFLEN], buf2[BUFLEN],line2[BUFLEN];
	int resources1,confidence1,resources2,confidence2;
	struct hostent *hp;
	char host[50];
	char *unit1,*unit2,*temp,*val1,*val2;
	char u1[20],v1[2],u2[20],v2[2];
	bzero(u1, 20);bzero(v1, 2);
	bzero(u2, 20);bzero(v2, 2);
	

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd==-1)
      err("socket");
    else 
     // printf("Server : Socket() successful\n");
    length = sizeof(my_addr);
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(PORT));
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //my_addr.sin_port=htons(atoi(argv[1]));
	
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))<0)
      err("bind");
    else
     // printf("Server : bind() successful\n");
	  bzero(buf, BUFLEN);
	bzero(buf2, BUFLEN);
	
	gethostname(host,50);
	hp=gethostbyname(host);
	
	if(hp==0)
		err("Unknown host");
	
	bcopy((char *)hp->h_addr, (char *)&my_addr.sin_addr,hp->h_length);
	printf("Major has UDP Port: %d and IP Address: %s for Phase 1\n",ntohs(my_addr.sin_port), inet_ntoa(my_addr.sin_addr));
// getsockname(sockfd, (struct sockaddr *)&sin, &slen1);
	
   
	   {//FOR CAPTAIN 1!
	    n=recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
		 
        if (n<0)
            err("Could not receive from Captain 1");
		
		 n=recvfrom(sockfd, buf2, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not receive from Captain 1");		
		printf("Major has now connected to Captain 1...\n");
		strcpy(line2,buf2);
		
		
		unit1=strtok(line,"$");     //PARSING
		strcpy(u1,unit1);
		//printf("Unit 1: %s\n",u1);
		val1=strtok(NULL,"\n");
		strcpy(v1,val1);
		//printf("Value 1: %s\n",v1);
		if(strcmp(unit1,"Resources")==0)
		{
		  resources1=v1[0]-48;
		  //printf("First one is RESOURCES\n");
		}
		else
		{
		  confidence1=v1[0]-48;
		  //printf("First one is CONFIDENCE\n");
		}
		
		unit2=strtok(line2,"$");
		strcpy(u2,unit2);
	//	printf("Unit 2: %s\n",u2);
		val2=strtok(NULL,"\n");
		strcpy(v2,val2);
	//	printf("Value 2: %s\n",v2);
		if(strcmp(unit2,"Resources")==0)
		{
		  resources1=v2[0]-48;
		  //printf("Second one is RESOURCES\n");
		}
		else
		{
		   confidence1=v2[0]-48;
		  //printf("Second one is CONFIDENCE\n");
		}
		
       /* printf("Received packet from %s:%d\nData: %s\n",
		        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);
		 printf("Received packet from %s:%d\nData: %s\n\n",
		        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf2);*/
        
		
		bzero(buf, BUFLEN);
		bzero(buf2, BUFLEN);
		
	 }//END OF CAPTAIN 1
	{//                      FOR CAPTAIN 2!!
	    n=recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
		 
        if (n<0)
            err("Could not Receive from Captain2");
		
		 n=recvfrom(sockfd, buf2, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not Receive from Captain2");		
		printf("Major has now connected to Captain 2...\n\n");
		strcpy(line2,buf2);
		
		
		unit1=strtok(line,"$");     //PARSING
		strcpy(u1,unit1);
		
		val1=strtok(NULL,"\n");
		strcpy(v1,val1);
		if(strcmp(unit1,"Resources")==0)
		{
		  resources2=v1[0]-48;		
		}
		else
		{
		  confidence2=v1[0]-48;
		}
		
		unit2=strtok(line2,"$");
		strcpy(u2,unit2);
		val2=strtok(NULL,"\n");
		strcpy(v2,val2);
		if(strcmp(unit2,"Resources")==0)
		{
		  resources2=v2[0]-48;
		}
		else
		{
		   confidence2=v2[0]-48;
		}
		 /*  printf("Received packet from %s:%d\nData: %s\n\n",
		        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf); 
           printf("Received packet from %s:%d\nData: %s\n\n",
		        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf2);*/	
		printf("Major has received the following:\n");
		printf("1. Captain 1: Resources - %d,  Confidence - %d\n",resources1,confidence1);
		printf("2. Captain 2: Resources - %d,  Confidence - %d\n",resources2,confidence2);
		printf("End of Phase 1 for Major\n");
		
	 }//END OF CAPTAIN 2
	
		bzero(buf, BUFLEN);
		bzero(buf2, BUFLEN);
		if(n<0)
		{
		  err("Send to");
		}
	

    close(sockfd);
    return 0;
}