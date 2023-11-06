#include<stdio.h>
#include<stdbool.h>
struct process{
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int obt;
};

struct process init(){
    struct process p1;
    p1.at=0;
    p1.bt=0;
    p1.wt=0;
    p1.ct=0;
    p1.tat=0;
    p1.obt=0;
    return p1;
};

struct queue{
    int front;
    int back;
    int arr[1000];
};

struct queue initilize(){
    struct queue q1;
    for(int i=0;i<1000;i++){
        q1.arr[i]=-1;
    }
    q1.front=-1;
    q1.back=-1;
    return q1;
};

void add(struct queue* q1,int ele){
    if(q1->front==-1){
        q1->front=0;
    }
    q1->back++;
    q1->arr[q1->back]=ele;
}

bool isempty(struct queue* q1){
    if(q1->front>q1->back){
        return true;
    }
    return false;
}
int getfront(struct queue* q1){
    int ele=q1->arr[q1->front];
    q1->front++;
    return ele;
}


void sortbyarrivaltime(struct process p[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                struct process p2=p[i];
                p[i]=p[j];
                p[j]=p2;
            }
        }
    }
}


void sortbybursttime(struct process p[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at!=p[j].at){
                break;
            }
            if(p[i].bt>p[j].bt){
                struct process p2=p[i];
                p[i]=p[j];
                p[j]=p2;
            }
        }
    }
}


void printProcess(struct process p[],int n){
    for(int i=0;i<n;i++){
        printf("%d  %d  %d %d  %d\n",p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
}



void rr(struct process p[],int n,int qt){
    struct queue x=initilize();


    int time=0;


    int vis[n];
    for(int i=0;i<n;i++){
        vis[i]=0;
    }


    while(1){


        for(int nw=0;nw<n;nw++){
                if(vis[nw]==0){
                if(time>=p[nw].at && p[nw].bt>0){
                        vis[nw]=1;
                        add(&x,nw);
                }
            }
        }


        printf("Printing Ready Q \n");
        if(!isempty(&x)){
            for(int i=x.front;i<=x.back;i++){
                printf("%d ",x.arr[i]);
            }
            printf("\n");
        }


        bool c=isempty(&x);
        if(!c){
            int cp=getfront(&x);
            if(p[cp].bt<=qt){
                time+=p[cp].bt;
                p[cp].ct=time;
                p[cp].tat= p[cp].ct-p[cp].at;
                p[cp].bt=0;
            }


            else{
                time+=qt;
                p[cp].bt-=qt;
                for(int nw=cp+1;nw<n;nw++){
                    if(vis[nw]==0){
                    if(time>=p[nw].at && p[nw].bt>0){
                            vis[nw]=1;
                            add(&x,nw);
                    }
                    }
                }
                add(&x,cp);
            }
        }  


        int f=1;
        for(int i=0;i<n;i++){
            if(p[i].bt!=0){
                f=0;
                break;
            }
        }


        if(f==0 && c){
            time++;
        }


        if(f==1){
            break;
        }

    }
}

int main(){
    int n;
    printf("Enter the number of process ");
    scanf("%d",&n);

    struct process p[n];
    for(int i=0;i<n;i++){
        p[i]=init();
    }
    
    printf("Enter arrival and burst time for each process");
    for(int i=0;i<n;i++){
        int ele;
        scanf("%d",&ele);
        p[i].at=ele;
        scanf("%d",&ele);
        p[i].bt=ele;
        p[i].obt=ele;
    }

    int qt=0;
    printf("Enter the quantum of process ");
    scanf("%d",&qt);


     sortbyarrivaltime(p,n);
     sortbybursttime(p,n);


    printf("\n\n");
    printProcess(p,n);
    rr(p,n,qt);
     printf("\n\n");

    for(int i=0;i<n;i++){
        p[i].wt=p[i].tat-p[i].obt;
    }
    printProcess(p,n);


    
}