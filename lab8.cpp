Lab 8: pthread
//1. Write a simple program to create a thread 
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
 
// Function to run in the thread
void* print_numbers(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("%d\n", i);
        sleep(1);  // Sleep for 1 second
    }
    return NULL;
}
 
int main() {
    pthread_t thread_id;
 
    // Create a thread
    if (pthread_create(&thread_id, NULL, print_numbers, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
 
    // Wait for the thread to finish
    pthread_join(thread_id, NULL);
 
    printf("Thread has finished execution.\n");
    return 0;
}
 
 
//2. Write a program to create two threads such that one thread will be calculating sum of the element of an array and other thread will be performing multiplication of the element of array
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define ARRAY_SIZE 5
 
// Shared array
int array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
 
// Variables to store results
int sum_result = 0;
int product_result = 1;
 
// Mutex for synchronizing access to shared data
pthread_mutex_t mutex;
 
void* calculate_sum(void* arg) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
 
    // Lock the mutex before updating shared data
    pthread_mutex_lock(&mutex);
    sum_result = sum;
    pthread_mutex_unlock(&mutex);
 
    return NULL;
}
 
void* calculate_product(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        product_result *= array[i];
    }
 
    // Lock the mutex before updating shared data
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
 
    return NULL;
}
 
int main() {
    pthread_t sum_thread, product_thread;
 
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
 
    // Create threads
    if (pthread_create(&sum_thread, NULL, calculate_sum, NULL) != 0) {
        perror("Failed to create sum thread");
        return 1;
    }
 
    if (pthread_create(&product_thread, NULL, calculate_product, NULL) != 0) {
        perror("Failed to create product thread");
        return 1;
    }
 
    // Wait for threads to finish
    pthread_join(sum_thread, NULL);
    pthread_join(product_thread, NULL);
 
    // Output results
    printf("Sum of array elements: %d\n", sum_result);
    printf("Product of array elements: %d\n", product_result);
 
    // Destroy mutex
    pthread_mutex_destroy(&mutex);
 
    return 0;
}
 
 
//3. Write a program to implement producer consumer problem using semaphore and multithreading 
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 
#define BUFFER_SIZE 5
 
// Shared buffer
int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
 
// Semaphores
sem_t empty; // Counts empty slots in the buffer
sem_t full;  // Counts filled slots in the buffer
pthread_mutex_t mutex; // Mutex for mutual exclusion
 
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Produce an item
        int item = rand() % 100; // Random item
        sem_wait(&empty); // Decrease empty count
        pthread_mutex_lock(&mutex); // Lock the buffer
 
        // Add the item to the buffer
        buffer[count++] = item;
        printf("Producer produced: %d\n", item);
 
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Increase full count
 
        sleep(1); // Simulate time taken to produce
    }
    return NULL;
}
 
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Decrease full count
        pthread_mutex_lock(&mutex); // Lock the buffer
 
        // Remove an item from the buffer
        int item = buffer[--count];
        printf("Consumer consumed: %d\n", item);
 
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Increase empty count
 
        sleep(2); // Simulate time taken to consume
    }
    return NULL;
}
 
int main() {
    pthread_t prod_thread, cons_thread;
 
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, the buffer is empty
    sem_init(&full, 0, 0); // Initially, there are no filled slots
    pthread_mutex_init(&mutex, NULL); // Initialize mutex
 
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
 
    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
 
    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
 
    return 0;
}
