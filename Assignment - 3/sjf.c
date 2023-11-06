#include<stdio.h>
#include<sys/types.h>

int time = 0;
struct process{
    int pId;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
};

struct process createProcess(int id, int at, int bt){
    struct process p1;
    p1.pId = id;
    p1.at = at;
    p1.bt = bt;
    return p1;
}

void bSortByArival(struct process processes[], int n){
    for(int i = 0 ; i < n-1 ; i++){
        for(int j = 0 ; j < n-i-1 ; j++ ){
            if(processes[j].at> processes[j+1].at){
                struct process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

void bSortByBurst2(struct process processes[], int n){
    for(int i = 0 ; i < n-1 ; i++){
        for(int j = 0 ; j < n-i-1 ; j++ ){
            if(processes[j].bt> processes[j+1].bt && time >= processes[j+1].at){
                struct process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

void bSortByBurst1(struct process processes[], int n){
    for(int i = 0 ; i < n-1 ; i++){
        for(int j = 0 ; j < n-i-1 ; j++ ){
            if(processes[j].bt> processes[j+1].bt && (processes[j].at == processes[j+1].at || time >= processes[j].bt)){
                struct process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

void schedule(struct process processes[],int n){
    bSortByBurst2(processes,n);
    int i = 0;
    while(i < n && processes[i].bt == 0){
        i++;
    }

    if(i == n){
        printf("scheduling is completed");
    }else{
        processes[i].bt-=1;
        time+=1;

        printf("processes : %d at : %d bt %d\n",processes[i].pId,processes[i].at,processes[i].bt);
    
        printf("\n");
        schedule(processes,4);

    }
}


int main()
{
    
    struct process processes[4];
    processes[0] = createProcess(1,0,5);
    processes[1] = createProcess(2,1,3);
    processes[2] = createProcess(3,2,4);
    processes[3] = createProcess(4,4,1);

    for(int i = 0 ; i < 4 ; i++){
        printf("processes : %d at : %d bt %d\n",processes[i].pId,processes[i].at,processes[i].bt);
    }

    bSortByArival(processes,4);
    bSortByBurst1(processes,4);

    printf("\n\n\n\n");
    schedule(processes,4);
}