// Online C compiler to run C program online
#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void display(int,int);
struct deadlock
{
    int a[10];
}allo[10] ,req[10],avail,work ;
int main() {
    int n, i ,m , j , l,complete =0,found =1,safe[10],ch =0 ,deadlock;
    bool finish[10] = {false};
    printf("Number of processes :");
    scanf("%d",&n);
    printf("number of max resources :");
    scanf("%d",&m);
        for(i = 0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("Allocate resources for process :%d :",i);
       scanf("%d",&allo[i].a[j]);
        }
        for(j=0;j<m;j++)
        {
       printf("number of max resources allocated for %d :",i);
       scanf("%d",&req[i].a[j]);
        }
   
    }
         for(int k =0;k<m;k++)
        {
            printf("Available resources :");
            scanf("%d",&avail.a[k]);
            work.a[k] = avail.a[k];
        }
    display(n,m);
    while(1)
    {
        deadlock =1;
        for(i=0;i<n;i++)
        {
            if(finish[i] == false)
            {
                found = 1;
                for(j=0 ;j<m;j++)
                {
                    if(req[i].a[j]>work.a[j])
                    {
                        found = 0;
                        break;
                    }
                }
                if(found!=0)
                {
                    for(j=0;j<m;j++)
                    {
                        work.a[j] = work.a[j] + allo[i].a[j];
                    }
                    safe[ch] = i;
                    ch++;
                    deadlock = 0;
               printf("\nProcess %d is executed\n",i);
               finish[i] = true;    
                }
            }
        }
              if(deadlock == 1)
      {
          printf("Deadlock detected , not in safe state");
          for(int l=0;l<n;l++)
          {
              if(finish[i] == false)
              {
                  printf(" Process : %d is involved in Deadlock\n",l);
              }
          }
          return 0;
      }
      complete =1;
      for(j =0 ;j<n;j++)
    {
        if(finish[j] == false)
        {
            complete = 0;
            break;
        }
    }
              if(complete == 1)
              {
                   printf("Safe Sequence");
                  for(i=0;i<ch;i++)
                  {
                     printf("%d\t",safe[i]);
                  }
                  return 0;
              }
    }
    return 0;
}
void display(int n , int m)
{
     printf("\nProcess\tAllocated\t req\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", allo[i].a[j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", req[i].a[j]);
        }
        printf("\n");
    }
}
