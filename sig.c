#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t signal;
void* vehicle(void*);

int main()
{
	pthread_t tid[4];
	sem_init(&signal,0,2);
	int i,v[4];
	for(i=0;i<4;i++)
	{
		v[i]=i;
		pthread_create(&tid[i],NULL,vehicle,(void*)&v[i]);
	}

	for(i=0;i<4;i++)
	{
		pthread_join(tid[i],NULL);
	}

	sem_destroy(&signal);
	return 0;
}

void* vehicle(void* v)
{
	int veh=*(int*)v;
	printf("Vehicle %d is waiting\n",veh);
	sem_wait(&signal);
	printf("Vehicle %d is moving\n",veh);
	sleep(5);
	sem_post(&signal);
	printf("Vehicle %d has finished\n",veh);
}
