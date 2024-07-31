/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:15:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/07/31 08:22:03 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void my_usleep(t_table *table, long time)
{
	long start_time;
	start_time = get_current_time();
	// && get_value(&table->table_lock, &table->dead_flag) == 0
	while(get_current_time() - start_time < time)
		usleep(100);
}

void	print(t_philo *philo, char *str)
{
	long time;
	
	pthread_mutex_lock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->table_lock);
	time = get_current_time() - philo->table->start_time;
	pthread_mutex_unlock(&philo->table->table_lock);
	printf(str, time, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

long	get_value(pthread_mutex_t *mutex, long *variable)
{
	long value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_value(pthread_mutex_t *mutex, long *variable, long value)
{
	pthread_mutex_lock(mutex);
	if (value == 0)
		*variable = *variable + 1;
	else 
		*variable = value;
	//pthread_mutex_unlock(mutex);
}

void	my_exit()
