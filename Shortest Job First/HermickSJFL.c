/* 
 * SER 334 | Fall 2020 | Programming 9 | Shortest-Job-First Scheduling
 * Description: Implements a program that simulates the Shortest-Job-First
 *              Scheduling algorithms (live and not live).
 * 
 * 
 * Completion Time: 10 hours
 * 
 * @author Emma Hermick 
 * @version 1.0 | Nov 15, 2020
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 2000

struct Process {
    int pid;
    int tau;
    float alpha;
    int t[MAXCHAR];
};

void sjf(struct Process *p, int ticks, int processes) {
    printf("\n==Shortest-Job-First==\n");
    int i, j, k;
    int time = 0;
    int turnaround = 0;
    int waiting = 0;
    int tmp;


    for (j = 0; j < ticks; j++) {
        printf("\nSimulating %dth tick of processes @ time %d:\n", j, time);
        
        int val = 0;

        //pNum = 0;
        for (i = 0; i < processes; i++) {

            //pNum = i;
            for (k = i + 1; k < processes; k++) {

                if (p[i].t[j] > p[k].t[j]) {
                    tmp = p[i].t[j];
                    p[i].t[j] = p[k].t[j];
                    p[k].t[j] = tmp;

                    tmp = p[i].pid;
                    p[i].pid = p[k].pid;
                    p[k].pid = tmp;
                   //p[i].pid = k;
                   //p[k].pid = i;
                    //pNum = k;

                }
                val = p[i].t[j];
            }
            
            printf("Process %d took %d.\n", p[i].pid, p[i].t[j]);
            time = time + p[i].t[j];
            turnaround = turnaround + p[i].t[j];
        }
        turnaround = turnaround + val;
        waiting = waiting + val;
    }
    
    printf("\nTurnaround Time: %d\n", turnaround);
    printf("Waiting Time: %d\n", waiting);
}

void sjfLive(struct Process *p, int ticks, int processes) {
    printf("\n==Shortest-Job-First Live==\n");
    int i, j, k;
    int time = 0;
    int turnaround = 0;
    int waiting = 0;
    int tmp;
    int est[processes];
    int estError = 0;
    int last;

    for (j = 0; j < ticks; j++) {
        printf("\nSimulating %dth tick of processes @ time %d:\n", j, time);
        
        int val = 0;

        for (i = 0; i < processes; i++) {
            p[i].pid = i;
            
            //First tick
            if (j == 0) {
                last = p[i].tau;
                est[i] = p[i].tau;
                //printf("\n\nEST = %d\n\n", p[i].tau);
            }
            
            else {
                last = p[i].t[j-1];
                //printf("\n\nEST = (%f * %d) + ( (1 - %f) * %d)\n\n", p[i].alpha, last, p[i].alpha, est[i]);
                est[i] = (p[i].alpha * last) + ( (1-p[i].alpha) * est[i]);
                
                    
                for (k = i + 1; k < processes; k++) {
                    int lastK = p[k].t[j-1];
                    int estK = (p[k].alpha * lastK) + ( (1-p[k].alpha) * estK);
                    
                    if (est[i] > estK) {
                        //printf("\n\nEst I = %d Est K = %d\n\n", est[i], estK);
                        tmp = p[i].t[j];
                        p[i].t[j] = p[k].t[j];
                        p[k].t[j] = tmp;

                        tmp = p[i].pid;
                        p[i].pid = p[k].pid;
                        p[k].pid = tmp;
                        //p[i].pid = k;
                        //p[k].pid = i;
                    }
                
                val = p[i].t[j];
                }
            }

            printf("Process %d was estimated for %d and took %d.\n", p[i].pid, est[i], p[i].t[j]);
            time = time + p[i].t[j];
            turnaround = turnaround + p[i].t[j];
            estError = estError + abs(p[i].t[j] - est[i]);
        }
        turnaround = turnaround + val;
        waiting = waiting + val;
    }
    
    printf("\nTurnaround Time: %d\n", turnaround);
    printf("Waiting Time: %d\n", waiting);
    printf("Estimation Error: %d\n", estError);
}

/*
 * 
 */
int main(int argc, char** argv) {
    char* input; 
    int i, j, k;
    int ticks, processes;
    struct Process *p;
    
    input = argv[1];
    printf("Input: %s \n", input);
    
    FILE *file;
    file = fopen(input, "r");
    
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    
    fscanf(file, "%d", &ticks);
    fscanf(file, "%d", &processes);

    printf("\nTicks: %d\n", ticks);
    printf("Processes: %d\n", processes);
    
    p = (struct Process*)calloc(processes, sizeof(struct Process));

        
    for (i = 0; i < processes; i++) {
        fscanf(file, "%d", &p[i].pid);
        fscanf(file, "%d", &p[i].tau);
        fscanf(file, "%f", &p[i].alpha);
        
        for (j = 0; j < ticks; j++) {
            fscanf(file, "%d", &p[i].t[j]);
        }
        
    }
    
    sjf(p, ticks, processes);
   

    free(p);
    fclose(file);
    
        file = fopen(input, "r");
    
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    
    fscanf(file, "%d", &ticks);
    fscanf(file, "%d", &processes);
    
    p = (struct Process*)calloc(processes, sizeof(struct Process));

        
    for (i = 0; i < processes; i++) {
        fscanf(file, "%d", &p[i].pid);
        fscanf(file, "%d", &p[i].tau);
        fscanf(file, "%f", &p[i].alpha);
        
        for (j = 0; j < ticks; j++) {
            fscanf(file, "%d", &p[i].t[j]);
        }
        
    }
    
    sjfLive(p, ticks, processes);
    
    free(p);
    fclose(file);
    
    return 0;
    
}

