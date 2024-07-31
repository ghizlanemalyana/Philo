/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 06:05:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/07/31 02:56:12 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dream(t_philo *philo)
{
	if (get_value(&philo->table->table_lock, &philo->table->dead_flag) == 1)
		return (0);
	print(philo, SLEEP);
	my_usleep(philo->table->time_to_sleep);
	return (1);
}

static int	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (table->number_of_meals != -2 && table->number_of_meals
		== get_value(&philo->lock, &philo->meals_counter))
		return (0);
	if (get_value(&table->table_lock, &table->dead_flag) == 1)
		return (0);
	pthread_mutex_lock(philo->r_fork);
	print(philo, HOLD_FORK);
	pthread_mutex_lock(philo->l_fork);
	print(philo, HOLD_FORK);
	set_value(&philo->lock, &philo->last_meal_time, get_current_time());
	print(philo, EAT);
	my_usleep(table->time_to_eat);
	set_value(&philo->lock, &philo->meals_counter, 0);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

void *philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!get_value(&philo->table->table_lock, &philo->table->start_time))
		;
	if (philo->id % 2 == 0)
		my_usleep(100); // to do
	set_value(&philo->lock, &philo->last_meal_time, get_current_time());
	while(1)
	{
		if (eat(philo) == 0)
			break ;
		if (dream(philo) == 0)
			break ;
		print(philo, THINK);
	}
	return(NULL);
}

