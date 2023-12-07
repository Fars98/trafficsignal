#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t north_south,south_north,east_west,west_east;

void* signal();
void* northtosouth();
void* southtonorth();
void* easttowest();
void* westtoeast();

int main()
{
        pthread_t light,north,south,east,west;

        sem_init(&north_south,0,1);
        sem_init(&south_north,0,1);
        sem_init(&east_west,0,1);
        sem_init(&west_east,0,1);

	pthread_create(&light,NULL,signal,NULL);
	pthread_create(&north,NULL,northtosouth,NULL);
        pthread_create(&south,NULL,southtonorth,NULL);
        pthread_create(&east,NULL,easttowest,NULL);
        pthread_create(&west,NULL,westtoeast,NULL);

	pthread_join(light,NULL);
        pthread_join(north,NULL);
        pthread_join(south,NULL);
        pthread_join(east,NULL);
        pthread_join(west,NULL);

        sem_destroy(&north_south);
        sem_destroy(&south_north);
        sem_destroy(&east_west);
        sem_destroy(&west_east);

        return 0;
}


void* signal()
{
        sem_wait(&east_west);
        sem_wait(&west_east);

        printf("Green in north-south direction\n");

        sem_post(&south_north);
        sem_post(&north_south);

        sleep(5);

        sem_wait(&north_south);
        sem_wait(&south_north);

        printf("Green in east-west direction\n");

        sem_post(&east_west);
        sem_post(&west_east);

        sleep(5);
}


void* northtosouth()
{
        sleep(1);
        sem_wait(&north_south);
        printf("Vehicles moving in north-south direction\n");
        sem_post(&north_south);
}

void* southtonorth()
{
        sleep(1);
        sem_wait(&south_north);
        printf("Vehicles moving in south-north direction\n");
        sem_post(&south_north);
}

void* easttowest()
{
        sleep(1);
        sem_wait(&east_west);
        printf("Vehicles moving in east-west direction\n");
        sem_post(&east_west);
}

void* westtoeast()
{
        sleep(1);
        sem_wait(&west_east);
        printf("Vehicles moving in west-east direction\n");
        sem_post(&west_east);
}

