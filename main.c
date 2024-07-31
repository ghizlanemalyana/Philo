#include <libc.h>
#include <pthread.h>

pthread_mutex_t table_lock;
pthread_mutex_t print_lock;


void	*routine(void *content)
{
	pthread_mutex_lock(&table_lock);
	*(int *)content = 10;
	pthread_mutex_unlock(&table_lock);

	return (NULL);
}

int main()
{
	int a = 1;
	int b = 2;

	pthread_t thread1;

	pthread_mutex_init(&table_lock, NULL);

	pthread_create(&thread1, NULL, routine, &a);

	sleep(10);

	pthread_mutex_lock(&table_lock);
	a = 100;
	pthread_mutex_unlock(&table_lock);

	// while (1)
	// 	;
}
