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
#define GENPORT "6587"    //General's UDP Port (Conn With Major)
#define CAPT1PORT 24087   //Capt.1's TCP Port
#define CAPT2PORT 24187   //Capt.2's TCP Port
#define GENTCP "6687"     //General's TCP Port

void err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in my_addr, cli_addr,sin,serv_addr,gen_addr;
    int sockfd, i, n, length, p1, p2, optval; 
    socklen_t slen=sizeof(cli_addr),slen1;
    char buf[BUFLEN], line[BUFLEN], buf2[BUFLEN],line2[BUFLEN],b[30],b2[30],c1[100],c2[100];
	struct hostent *hp, *h;
	char host[50],file[30]="passGn.txt";
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
    my_addr.sin_port = htons(atoi(GENPORT));
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
	printf("General has UDP Port: %s and IP Address: %s for Phase 2\n",GENPORT, inet_ntoa(my_addr.sin_addr));
// getsockname(sockfd, (struct sockaddr *)&sin, &slen1);
	
   
	   {//FROM MAJOR
	    n=recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
		 
        if (n<0)
            err("Could not receive from Major");
			
		 n=recvfrom(sockfd, buf2, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not receive from Captain 1");	
			
			//SUCCESS RATES
			 n=recvfrom(sockfd, v1, 2, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
	  if (n<0)
            err("Could not receive port from Major");
			
	 n=recvfrom(sockfd, v2, 2, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not receive password from Major");	
		p1=v1[0];
		p2=v2[0];
		printf("Received the Password from Major\n");
	//	printf("Port number sent by Major: %s\n",buf);
	//	printf("Password sent by Major is: %s\n",buf2);
		}
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
	while((strcmp(buf,b)!=0)||(strcmp(buf2,b2)!=0))
	{
	 fclose(fptr);
	bzero(buf, BUFLEN);
		bzero(buf2, BUFLEN);
	  printf("Wrong Password from Major, try again\n");
	  n=recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
	  if (n<0)
            err("Could not receive port from Major");
			
	 n=recvfrom(sockfd, buf2, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not receive password from Major");	
	 //SUCCESS RATE
	  n=recvfrom(sockfd, v1, 2, 0, (struct sockaddr*)&cli_addr, &slen);
		 strcpy(line,buf);
	  if (n<0)
            err("Could not receive port from Major");
			
	 n=recvfrom(sockfd, v2, 2, 0, (struct sockaddr*)&cli_addr, &slen);
        if (n<0)
            err("Could not receive password from Major");	
		
		p1=v1[0];
		p2=v2[0];
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
		//printf("Compare %s: %s\n",buf,b);
		//printf("Compare %s: %s\n",buf2,b2);
	}
	}
	printf("Correct Password from Major\n");
	printf("Success Rate of Captain 1 = %d\n",p1);
	printf("Success Rate of Captain 2 = %d\n",p2);
	printf("End of Phase 2 for the General\n");
	}
	printf("----------------------------------------------------------\n");
		close(sockfd);
		
		
		/* --------------------------------------PHASE 3 FOR GENERAL STARTING--------------------------------------------*/
	bzero(c1, 100);
    bzero(c2, 100);	
	
	/* length = sizeof(gen_addr);
    bzero(&gen_addr, sizeof(gen_addr));
    gen_addr.sin_family = AF_INET;
    gen_addr.sin_port = htons(atoi(GENTCP));
  //  gen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gethostname(host,50);
	h=gethostbyname(host);
	if(h==0)
		printf("Unknown host");	
	bcopy((char *)h->h_addr, (char *)&gen_addr.sin_addr,h->h_length);
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))<0)
      err("bind");*/
	if(p1>p2)
	{
	   strcpy(c1,"start");
	   strcpy(c2,"backup");
	}
	else
	{
	  strcpy(c1,"backup");
	   strcpy(c2,"start");
	}
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
	length = sizeof(gen_addr);
    bzero(&gen_addr, sizeof(gen_addr));
    gen_addr.sin_family = AF_INET;
    gen_addr.sin_port = htons(atoi(GENTCP));
  //  gen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gethostname(host,50);
	h=gethostbyname(host);
	if(h==0)
		printf("Unknown host");	
	bcopy((char *)h->h_addr, (char *)&gen_addr.sin_addr,h->h_length);
	
	// set SO_REUSEADDR on a socket to true (1):
    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))<0)
      err("bind");
	
	
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CAPT1PORT); 
    gethostname(host,50);
	h=gethostbyname(host);
	if(h==0)
		printf("Unknown host");	
	bcopy((char *)h->h_addr, (char *)&serv_addr.sin_addr,h->h_length);
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
     n=send(sockfd,c1,strlen(c1),0); 
  //  sleep(2);
	 
    if(n < 0)   
        printf("\n Send error \n");
	close(sockfd);
	//	sleep(1);
		
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CAPT2PORT); 
    gethostname(host,50);
	h=gethostbyname(host);
	if(h==0)
		printf("Unknown host");	
	bcopy((char *)h->h_addr, (char *)&serv_addr.sin_addr,h->h_length);
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
	 n=send(sockfd,c2,strlen(c2),0); 	 
//	 sleep(2);
    if(n < 0)   
        printf("\n Send error \n");
		
		 getsockname(sockfd, (struct sockaddr *)&cli_addr, &slen1);
	 printf("General has TCP Port: %d and IP Address: %s\n", ntohs(gen_addr.sin_port),inet_ntoa(gen_addr.sin_addr));
	 if(p1>p2)
	 {
	   printf("Captain 1 has the highest probability of success\n");
	   printf("Command to start the mission sent to Captain 1\n");
	   printf("Command to be the backup for the mission sent to Captain 2\n");
	  }
	 else
	 {
	   printf("Captain 2 has the highest probability of success\n");
	   printf("Command to start the mission sent to Captain 2\n");
	   printf("Command to be the backup for the mission sent to Captain 1\n");
	  }
	 printf("End of phase 3 for the General\n");
	 printf("----------------------------------------------------------\n");
	close(sockfd);
	return 0;
	}