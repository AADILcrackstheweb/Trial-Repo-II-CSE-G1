#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//declaring semaphores
sem_t vacant_seats;
sem_t eating;


#define NUM_SEATS 5 //according to the given problem

//declaring variables for tracking
int vacancies = NUM_SEATS;
bool seats_full = false;
int num_customers = -1; //getting the number of customers


//to_dine() checks if a customer can dine or has to wait
void to_dine()
{
    sem_wait(&eating);

    //the customer waits for the vacant_seats semaphore to be greater than zero
    while (seats_full || vacancies == 0) {
        sem_post(&eating);
        sem_wait(&vacant_seats);
        sem_wait(&eating);
    }

    vacancies--; //after each seat is occupied, vacancy is decremented
    printf("Thread ID: %ld has a seat! Vacancies left: %d\n", pthread_self(), vacancies);
    if (vacancies == 0) {
        seats_full = true; //all seats are filled
    }

    sem_post(&eating);
}

//to_rise() is called after the customer has finished eating
void to_rise()
{
    sem_wait(&eating);
    printf("Thread ID: %ld has finished dining!\n", pthread_self());
    vacancies++; //afer each seat is left, vacancy is incremented
    //the party has left
    if (vacancies == NUM_SEATS) {
        seats_full = false; //all seats are empty
        sem_post(&vacant_seats);
    }
    sem_post(&eating);
}

//calls the respective functions and also the main function for threads (i.e. customers)
void *transfer()
{
    to_dine();
    sleep(4); //the customer eats for 4 seconds
    to_rise();
    pthread_exit(NULL);
}

int main()
{
    //num_customers must be positive
    while (num_customers <= 0){
        printf("\nEnter the number of customers: ");
        scanf("%d", &num_customers);
    }

    //initializing the semaphores
    sem_init(&vacant_seats, 0, NUM_SEATS);
    sem_init(&eating, 0, 1);

    //creating an array of threads of size 'num_customers'
    pthread_t threads[num_customers];

    //each thread is created
    for (int i = 0; i < num_customers; i++){
        pthread_create(&threads[i], NULL, transfer, NULL);
    }

    //each thread (i.e. customer) is called
    for (int i = 0; i < num_customers; i++){
        pthread_join(threads[i], NULL);
    }

    //semaphores are destroyed for efficient memory management
    sem_destroy(&eating);
    sem_destroy(&vacant_seats);

    return 0;
}
