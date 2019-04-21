#include<stdio.h>
struct process
{
 int name;
 int at,bt,wt,tt,rt;
 int completed;
}p[10];

int n;
int q[10];  //queue created
int front=-1,rear=-1;
void enqueue(int i)
{
    if(rear==10)
        printf("overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;

}

int dequeue()
{
    if(front==-1)
        printf("underflow");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return 1;
    }
    return 0;
}

void sortByArrival() //sorting bubble
{
    struct process temp;
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].at>p[j].at)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

void main()
{
    int i,j,time=0,sum_bt=0,tq;
    char c;
    float avgwt=0,avgtt=0;
     printf("\nEnter Number of Processes:\n");
     scanf("%d",&n);
     for(i=0,c=1;i<n;i++,c++)
     {
         p[i].name=c;
         printf("\n Process %d\n",c);
         printf("\n Arrival Time :");
         scanf("%d",&p[i].at);
         printf(" Burst Time :");
         scanf("%d",&p[i].bt);
         p[i].rt=p[i].bt;    //we r initaializing burst time as remaining time
         p[i].completed=0;
         sum_bt+=p[i].bt;
    }
    printf("\nEnter the time quantum:");
    scanf("%d",&tq);
    sortByArrival();
    enqueue(0);          // first process in the queue
    printf("Process execution order: ");
    for(time=p[0].at;time<sum_bt;)       // process will run till total burst time
    {
        i=dequeue();
        if(p[i].rt<=tq)
        {                          //for processes which have tq greater than remaingtime

            time+=p[i].rt;
            p[i].rt=0;
            p[i].completed=1;
            printf(" %d ",p[i].name);
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tt=time-p[i].at;
            for(j=0;j<n;j++)     //adding nest process in queue if it is available?
            {
                if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        else               // time quantum lessthan remtime
        {
            time+=tq;
            p[i].rt=p[i].rt-tq;
            printf(" %d ",p[i].name);
            for(j=0;j<n;j++)    //adding nest process in queue if it is available?
            {
                if(p[j].at<=time && p[j].completed!=1 && i!=j && isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);   // Add the reaming process in queue again which is not completw\ed.
        }
    }

    printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");
    for(i=0;i<n;i++)
    {
        avgwt=avgwt+p[i].wt;
        avgtt=avgtt+p[i].tt;
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].tt);
    }
    printf("\nAverage waiting time:%f\n",avgwt/n);
    printf("\nAverage turnaround time:%f\n",avgtt/n);
}
