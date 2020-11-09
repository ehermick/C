/* 
 * SER 334 | Fall 2020 | Programming 7 | Implementing Load Balancing
 * Description: InstanceHost.c simulates a cloud-like server instance host.
 * 
 * Initializes the host environment, shuts down the host environment, and
 * creates a new server instance (thread)
 * 
 * Completion Time: 10 hours
 * 
 * @author Emma Hermick 
 * @version 1.0 | Nov 08, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "InstanceHost.h"
#include <pthread.h>

//Spawns the thread
struct host {
    pthread_t* threads; //list of threads
    int numThreads;
    
};


//Forward Declarations
void* runner(void *param);

pthread_mutex_t* lock;

/**
* Initializes the host environment.
*/
host* host_create() {
    host* h = (struct host*)malloc(sizeof(host));
    h->numThreads = 0; //start at 0
    
    pthread_t* t = (pthread_t*)malloc(sizeof(pthread_t));
    
    h->threads = t;
    
    return h;
}


/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_destroy(host** h) {
    free(*h);
    *h = NULL;
}

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host* h, struct job_node* batch) {
    printf("\nLoadBalancer: Received batch and spinning up new instance.\n\n");
    
    
    pthread_t tid; //thread id
    pthread_attr_t attr; //thread attributes
    
    lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    
    pthread_mutex_init(lock, NULL);
    
    while(batch->next != NULL) {
        pthread_create(&tid, &attr, runner, (void*)batch->data);
        pthread_join(tid, NULL);
    }
    
    batch->data_result = batch->data * batch->data; 
    
    pthread_mutex_destroy(lock);
    free(lock);
    
    host_destroy(&h);

}

void* runner(void *param) {

    pthread_exit(0); //exit thread
}


