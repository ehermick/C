/* 
 * SER 334 | Fall 2020 | Programming 7 | Implementing Load Balancing
 * Description: LoadBalancer.c simulates a load balancer
 * 
 * Initializes the load balancer, shuts down the load balancer, and adds a 
 * job to the load balancer
 * 
 * Completion Time: 10 hours
 * 
 * @author Emma Hermick 
 * @version 1.0 | Nov 08, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "LoadBalancer.h"
#include <pthread.h>

struct balancer {
    int batchSize; //Batch size
    int numJobs; //Number of jobs
    struct host* host;//instance host
    struct job_node* listJobs; //List of jobs
    pthread_mutex_t* lock; //Mutex lock
};

int bSize; //Global var to store batch size
//pthread_mutex_t lock;

/**
 * Initializes the load balancer. Takes batch size as parameter.
 */
balancer* balancer_create(int batch_size) {
    balancer* bal = (balancer*)malloc(sizeof(balancer));
    
    //Array to hold list of jobs
    bal->listJobs = (struct job_node*)malloc(sizeof(struct job_node) * batch_size);
    
    //Mutex lock
    pthread_mutex_init(&bal->lock, NULL);
    
    bal->batchSize = batch_size;
    bSize = batch_size;
    
    bal->numJobs = 0; //start at 0
    bal->host = host_create(); //create new host
    
    return bal; //return balancer
    
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_destroy(balancer** lb) {
    //pthread_mutex_destroy(&lb->lock);
    free(*lb);
    *lb = NULL;
}

/**
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 * 
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */
void balancer_add_job(balancer* lb, int user_id, int data, int* data_return) {
    printf("LoadBalancer: Received new job from user #%d to process data=%d and "
            "store it at %p.\n", user_id, data, data_return);
   
    pthread_mutex_lock(&lb->lock);
    
    lb->numJobs++; //Increment number of jobs
    

    //Build list of job
    struct job_node* job = (struct job_node*)malloc(sizeof(struct job_node));
    //Assign values
    job->data = data; 
    job->data_result = data_return;
    job->next = lb->listJobs; //Add job to front of list
    
    lb->listJobs = job; //Add job to job list
    
    //Enough jobs to fill batch
    if (lb->numJobs == bSize) {
        
        //Request new instance
        host_request_instance(lb->host, lb->listJobs);
        lb->numJobs = 0;

    }
    

    pthread_mutex_unlock(&lb->lock);
    free(job);
 
}