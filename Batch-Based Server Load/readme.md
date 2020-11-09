# Batch-Based Server Load Balancing Using Mutexes #

## HermickInstanceHost.c ##
- host_create : Initializes the host environment
- host_destroy : Shuts down the host environment
- host_request_instance : Creates a new server instance to handle processing the items contained in a batch

## HermickLoadBalancer.c ##
### Simulates a load balancer ###
- balancer_create : Initializes the load balancer
- balancer_destroy : Shuts down the load balancer
- balancer_add_job : Adds a job to the load balancer
