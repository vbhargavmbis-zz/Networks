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
#define PORT 6187
void err(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
 
   pid_t pid = 0;
   pid=fork();
   if(pid > 0)//PARENT PROCESS - CAPTAIN 1
   {
    struct sockaddr_in serv_addr,from, cli_addr;
	socklen_t slen1;
    int sockfd, i, slen=sizeof(serv_addr),n;
	struct hostent *h;
    char buf[BUFLEN], b[20], b2[20], host[50], file[30]="Captain1.txt";
	char *unit1,*unit2,*temp,*val1,*val2;
	char u1[10],v1[2],u2[10],v2[2];
	bzero(u1, 10);bzero(v1, 2);
	bzero(u2, 10);bzero(v2, 2);
//	int val1,val2;
   FILE *fptr;
   fptr=fopen(file,"rt");
   if(fptr==NULL)
   {
     printf("Could not open file\n");
   }
   else
   {
    fscanf(fptr,"%s",&b);
	fscanf(fptr,"%s",&b2);
	
    sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    if (sockfd ==-1)
        err("socket");
	serv_addr.sin_family = AF_INET;
	gethostname(host,50);
	h=gethostbyname(host);
	if(h==0)
		err("Unknown host");
	bcopy((char *)h->h_addr, (char *)&serv_addr.sin_addr,h->h_length);
	serv_addr.sin_port=htons(PORT);
    getsockname(sockfd, (struct sockaddr *)&cli_addr, &slen1);
	//printf("Captain 1 has IP Address %s and Port No %d\n",inet_ntoa(serv_addr.sin_addr), ntohs(cli_addr.sin_port));
	
	bzero(buf, BUFLEN);
    
	
   // while(1)
    {
     // fgets(buf,BUFLEN,stdin);
      n=sendto(sockfd, b, strlen(b), 0, (struct sockaddr*)&serv_addr, slen);
	   getsockname(sockfd, (struct sockaddr *)&cli_addr, &slen1);
	  printf("Captain 1 has UDP Port: %d and IP Address: %s\n", ntohs(cli_addr.sin_port),inet_ntoa(serv_addr.sin_addr));
      printf("Sending log file to the Major\n");
	  if(n<0)
	  {
	    err("Unit 1 not sent\n");
	  }
	
	   n=sendto(sockfd, b2, strlen(b2), 0, (struct sockaddr*)&serv_addr, slen);
      
	  if(n<0)
	  {
	    err("Value 1 not sent\n");
	  }
	  
	  printf("End of Phase 1 for Captain 1\n");
	printf("\n------------------------------------\n");
	  bzero(buf, BUFLEN);
    }
    close(sockfd);
	fclose(fptr);
   }
  }
   else if(pid == 0)//CHILD PROCESS - CAPTAIN 2
   {
     sleep(1);
      struct sockaddr_in serv_addr,from, cli_addr, foo;
	socklen_t slen1;
    int sockfd, i, slen=sizeof(serv_addr),n;
	struct hostent *h;
	char host[50];
    char buf[BUFLEN], b[20], b2[20], file[30]="Captain2.txt";

   FILE *fptr;
   fptr=fopen(file,"rt");
   if(fptr==NULL)
   {
     printf("Could not open file\n");
   }
   else
   {
    fscanf(fptr,"%s",&b);
	fscanf(fptr,"%s",&b2);
	
    sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    if (sockfd ==-1)
        err("socket");
	serv_addr.sin_family = AF_INET;
	gethostname(host,50);
	h=gethostbyname(host);
	//h=gethostbyname("nunki.usc.edu");
	if(h==0)
		err("Unknown host");
	
	bcopy((char *)h->h_addr, (char *)&serv_addr.sin_addr,h->h_length);
	serv_addr.sin_port=htons(PORT);
	
    getsockname(sockfd, (struct sockaddr *)&cli_addr, &slen1);
	//	 printf("Captain 2 has IP Address: %s and Port No: %d\n",inet_ntoa(serv_addr.sin_addr), ntohs(cli_addr.sin_port));
	// printf("Captain 2 has IP Address: %s and Port No: %d\n",inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
	//printf("Captain 2 has IP Address %s and Port No %d\n",inet_ntoa(foo.sin_addr),ntohs(foo.sin_port));
	bzero(buf, BUFLEN);
  //  printf("Sending log file to the Major\n");
	
  //SEND INFO
      n=sendto(sockfd, b, strlen(b), 0, (struct sockaddr*)&serv_addr, slen);
       getsockname(sockfd, (struct sockaddr *)&cli_addr, &slen1);
	  printf("\nCaptain 2 has UDP Port: %d and IP Address: %s\n",ntohs(cli_addr.sin_port),inet_ntoa(serv_addr.sin_addr));
      printf("Sending log file to the Major\n");
	  if(n<0)
	  {
	    err("Line 1 not sent\n");
	  }
	
      n=sendto(sockfd, b2, strlen(b2), 0, (struct sockaddr*)&serv_addr, slen);
	
	  if(n<0)
	  {
	    err("Line 2 not sent\n");
	  }
	      
	  printf("End of Phase 1 for Captain 2\n");
	
	  bzero(buf, BUFLEN);
    
    close(sockfd);
	fclose(fptr);
   }
   }
   return 0;
 }