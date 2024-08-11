/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:15:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/11 14:57:38 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_usleep(t_table *table, long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time
		&& (get_value(&table->table_lock, &table->dead_flag) == 0))
		usleep(100);
}

void	print(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->table->print_lock);
	time = get_current_time() - get_value(&philo->table->table_lock,
			&philo->table->start_time);
	if (get_value(&philo->table->table_lock, &philo->table->dead_flag) == 0)
		printf(str, time, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

long	get_value(pthread_mutex_t *mutex, long *variable)
{
	long	value;

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
	pthread_mutex_unlock(mutex);
}
