#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 


typedef int buffer_item;
#define BUFFER_SIZE 7
buffer_item buffer[BUFFER_SIZE];
int insertIndex;
int removeIndex;

sem_t full;
sem_t empty;
pthread_mutex_t mutex;

unsigned int seed;

int SLEEP_TIME;


void printBuffer() {
    printf("\t\tPrinting Buffer: [");
    int i;
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", buffer[i]); 
    }
    printf("]\n");

}

int insert_item(buffer_item item) {

    if (buffer[insertIndex] != '\0') {
        return -1;

    } else {
        buffer[insertIndex] = item;

        insertIndex++;
        insertIndex = insertIndex % BUFFER_SIZE;

        printf("---> Produced: %d\n", item);
        printBuffer();
        return 0;

    }

}

int remove_item(buffer_item item) {

    if (buffer[removeIndex] == '\0') {
        return -1;

    } else {
        buffer_item removedItem = buffer[removeIndex];
        buffer[removeIndex] = '\0';

        removeIndex++;
        removeIndex = removeIndex % BUFFER_SIZE;

        printf("<--- Consumed: %d\n", removedItem);
        printBuffer();
        return 0;

    }

}

void *producer(void *param) {
    buffer_item item;
    while (1) {
        printf("in producer.\n");
        sleep(rand_r(&seed) % SLEEP_TIME + 1);

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        printf("in producer critical section.\n");

        item = rand_r(&seed);

        if (insert_item(item) < 0) {
            printf("Could not insert into buffer. An item already exists!\n");

        }


        pthread_mutex_unlock(&mutex);

        sem_post(&full);

    }

}

void *consumer(void *param) {
    buffer_item *item = (int *)malloc(sizeof(int));
    while (1) {
        printf("in consumer.\n");

        sleep(rand_r(&seed) % SLEEP_TIME + 1);

        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        printf("in consumer critical section.\n");


        if (remove_item(*item) < 0) {
            printf("Could not remove from buffer. The item does not exist!\n");
        }


        pthread_mutex_unlock(&mutex);

        sem_post(&empty);

    }
    free(item);
}


int main(int argc, char*argv[]) {

    int producerCount;
    int consumerCount;

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        printf("Enter 3 arguments: sleep time, number of producers, number of consumers. \n");
        return -1;

    } else {
        SLEEP_TIME = atoi(argv[1]);
        producerCount = atoi(argv[2]);
        consumerCount = atoi(argv[3]);

    }


    seed = (unsigned int)time(NULL);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_t producers[producerCount];
    int i;
    for (i = 0; i < producerCount; i++) {
        pthread_attr_t pt_attr;

        pthread_attr_init(&pt_attr);

        int producerResults = pthread_create(&producers[i], &pt_attr, producer, NULL);
        if (producerResults == -1) {
            printf("Error creating producer thread.\n");

        }

    }

    pthread_t consumers[consumerCount];
    for (i = 0; i < consumerCount; i++) {
        pthread_attr_t ct_attr;

        pthread_attr_init(&ct_attr);

        int consumerResults = pthread_create(&consumers[i], &ct_attr, consumer, NULL);
        if (consumerResults == -1) {
            printf("Error creating consumer thread.\n");

        }

    }

    sleep(SLEEP_TIME);

    for(i = 0; i < producerCount; i++)
        pthread_cancel(producers[i]);
    for(i = 0; i < consumerCount; i++)
        pthread_cancel(consumers[i]);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}

