#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t north_south;
sem_t south_north;
sem_t east_west;
sem_t west_east;

void* northtosouth();
void* southtonorth();
void* easttowest();
void* westtoeast();

int main()
{
        pthread_t t1,t2,t3,t4;

        sem_init(&north_south,0,1);
        sem_init(&south_north,0,1);
        sem_init(&east_west,0,1);
        sem_init(&west_east,0,1);

        pthread_create(&t1,NULL,northtosouth,NULL);
        pthread_create(&t2,NULL,southtonorth,NULL);
        pthread_create(&t3,NULL,easttowest,NULL);
        pthread_create(&t4,NULL,westtoeast,NULL);

        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_join(t3,NULL);
        pthread_join(t4,NULL);

        sem_destroy(&north_south);
        sem_destroy(&south_north);
        sem_destroy(&east_west);
        sem_destroy(&west_east);

        return 0;
}


void* northtosouth()
{
        printf("Vehicles waiting for north to south\n");
        sem_wait(&east_west);
        printf("East to west clear\n");
        sem_wait(&west_east);
        printf("West to east clear\n");
        sem_wait(&north_south);
        printf("North to south clear\n");
        printf("Vehicles moving north to south\n");
        sleep(5);

        sem_post(&north_south);
        sem_post(&west_east);
        sem_post(&east_west);

        printf("North to south vehicles finished moving\n\n");
}

void* southtonorth()
{
        printf("Vehicles waiting for south to north\n");
        sem_wait(&east_west);
        printf("East to west clear\n");
        sem_wait(&west_east);
        printf("West to east clear\n");
        sem_wait(&south_north);
        printf("South to north clear\n");
        printf("Vehicles moving south to north\n");
        sleep(5);

        sem_post(&south_north);
        sem_post(&west_east);
        sem_post(&east_west);

        printf("South to north vehicles finished moving\n\n");

}
void* easttowest()
{
        printf("Vehicles waiting for east to west\n");
        sem_wait(&east_west);
        printf("East to west clear\n");
        sem_wait(&north_south);
        printf("North to south clear\n");
        sem_wait(&south_north);
        printf("South to north clear\n");

        printf("Vehicles moving east to west\n");
        sleep(5);

        sem_post(&south_north);
        sem_post(&north_south);
        sem_post(&east_west);

        printf("East to west vehicles finished moving\n\n");

}
void* westtoeast()
{
        printf("Vehicles waiting for west to east\n");
        sem_wait(&west_east);
        printf("West to east clear\n");
        sem_wait(&north_south);
        printf("North to south clear\n");
	sem_wait(&south_north);
        printf("South to north clear\n");
	printf("Vehicles moving west to east\n");
        sleep(5);
	sem_post(&south_north);
        sem_post(&north_south);
        sem_post(&west_east);
	printf("West to east Vehicles finished moving\n\n");

}

