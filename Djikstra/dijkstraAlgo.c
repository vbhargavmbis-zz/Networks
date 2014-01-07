#include<string.h>
#include <stdio.h>
#include <stdlib.h>


int x[]={0,1,2,3,4,5};
int source,r,e=0,ctr,f=0;
int d[7],p[7],explored[6],final[6];
int node[6][6];
char src;
char map(int a)
{
    if(a==0)
      return 'A';
    else if(a==1)
      return 'B';
    else if(a==2)
      return 'C';
    else if(a==3)
      return 'D';
    else if(a==4)
      return 'E';
    else if(a==5)
      return 'F';
}
int demap(char c)
{
    if((c=='A')||(c=='a'))
    {
     return 0;
     }
    else if((c=='B')||(c=='b'))
     return 1;
    else if((c=='C')||(c=='c'))
     return 2;
    else if((c=='D')||(c=='d'))
     return 3;
    else if((c=='E')||(c=='e'))
     return 4;
    else if((c=='F')||(c=='f'))
     return 5;
}

int getgraph()
{
     char d,ch;
  int cost,i,j;
     for(i=0;i<6;i++)
            {
              for(j=0;j<6;j++)
              {
                node[i][j]=99;
                }
            }
            char b[6];
  
  int c;
  int x,y;
  char start[2];
  char address[100]="node_a.txt";
  FILE *fptr;
        int character;
        for(c=0;c<6;c++)
        {
          //CHANGE ADDRESS IF REQUIRED HERE
         if(c==0)
          strcpy(address,"node_a.txt");
          else if(c==1)
            strcpy(address,"node_b.txt");
          else if(c==2)
            strcpy(address,"node_c.txt");
          else if(c==3)
            strcpy(address,"node_d.txt");
          else if(c==4)
            strcpy(address,"node_e.txt"); 
          else if(c==5)
            strcpy(address,"node_f.txt"); 
            
        fptr=fopen(address, "rt"); 
        if (fptr==NULL) 
        { 
        printf("%s",address);
                printf("Could not open file!\n"); // error in opening file
               // getch();
                return 1; 
        }
        else
        {
           // printf("File opened\n");
            fscanf(fptr,"%s",&b);
         //   printf("%s",b);
            fscanf(fptr,"%s",&start);//node[0] is the node name
         //   printf("%c\n",start[0]);
            x=demap(start[0]);
            
            while(!feof(fptr)) 
            {
              fscanf(fptr,"%s\t%d\t%c",&b,&cost,&ch);
             // printf("%c %d\n",b[0],cost);    
              y=demap(b[0]);
          //    printf("node[%d][%d]\n",x,y);
              node[x][y]=cost;
                      
            }
             fclose(fptr); /* close the file */
        }
     }
}


void initialize()
{
     int i;
     d[source]=0;
     for(i=0;i<6;i++)
     {
       if(i==source)
         d[source]=0;
       else
       {
           d[i]=99;
        }
 //       printf("%d ",d[i]);
     }
 //    printf("\n");
}
int unex[6],ue=0;
void choose()
{
     ue=0;
     int i,less=99;
     for(i=0;i<6;i++)
     {
       if(x[i]!=99)
       {
         unex[ue]=i;
         
//          printf("%d",unex[ue]);
          ue++;
        }
      
      }
     
//     printf("\n");
      less=d[unex[0]];
      r=unex[0];
     for(i=0;i<ue;i++)
     {
       if(d[unex[i]]<less)
       {
         less=d[unex[i]];
         r=unex[i];
       }
     }
    
//     printf("Least is: %d, R= %d\n",less,r);
}
int main(int argc, char *argv[])
{
    getgraph();
    int i,j,count=0;
    printf("Enter the source node\n");
    scanf("%c",&src);
    source=demap(src);
    r=source;
    initialize();
    while(count<6)
   // while((x[0]!=99) && (x[1]!=99) && (x[2]!=99) && x[3]!=99 && x[4]!=99 && x[5]!=99)
    {
       choose();
       for(i=0;i<6;i++)
       {
         if(node[r][i]<99)//if there is a path
         {
           if(d[i]>d[r]+node[r][i])//if value of bubble is > the new cost to get to that node
           {
             d[i]=d[r]+node[r][i];
             p[i]=r;

//             printf("d[%d]: %d, p[%d]: %d\n",i,d[i],i,p[i]);
           }
         }
       }
       x[r]=99;
                    
       count++;      
       
//       printf("\n\n");
     }
    
     
  printf("Shortest Path From %c to x:\t|  Total Cost\n",map(source));
  printf("---------------------------------------------\n");
  
    for(i=0;i<6;i++)
     {
       printf("From %c to %c:    ",map(source),map(i));
       if(i!=source)
       {
              ctr=i;
       // printf("%c->",map(ctr));
       final[f]=map(ctr);
       f++;
       while(p[ctr]!=source)
       {
         //printf("%c->",map(p[ctr]));
         final[f]=map(p[ctr]);
         f++;
         ctr=p[ctr];
       }
       final[f]=map(p[ctr]);
       f++;
       //printf("%c\n",map(p[ctr]));
       for(j=f-1;j>=0;j--)
       {
         printf("%c",final[j]);                
       } 
       printf("\t\t|    %d",d[i]);
       printf("\n");
       f=0;
       }
       else
       {
           printf("-\t\t|    -\n");
       }
     }
}
