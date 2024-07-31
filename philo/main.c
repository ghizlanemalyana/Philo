/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:21:31 by gmalyana          #+#    #+#             */
/*   Updated: 2024/07/31 04:51:33 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int full_philo(t_table *table)
{
	int		i = 0;
	t_philo	*philo;

	if (table->number_of_meals == -2)
		return (0);
	while (i < table->number_of_philos)
	{
		philo = &table->philos[i];
		if(get_value(&philo->lock, &philo->meals_counter) 
			!= table->number_of_meals)
			return (0);
		i++;
	}
	return (1);
}

int dead_philo(t_philo *philo)
{
	t_table *table;
	long res;

	table = philo->table;
	res = get_current_time() - get_value(&philo->lock, &philo->last_meal_time)
		> table->time_to_die;
	if (res == 1) // dead_philo
	{
		// set_value(&table->table_lock, &table->dead_flag, 1);
		pthread_mutex_lock(&table->print_lock);
		pthread_mutex_lock(&table->table_lock);
		printf(DIE, get_current_time() - table->start_time, philo->id);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->table_lock);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	return (0);
}

void monitoring(t_table *table)
{
	int i;
	
	my_usleep(table, table->time_to_die);
	while (1)
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (full_philo(table) || dead_philo(&table->philos[i]))
				return (my_exit(table));
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	t_table 		table;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (argc != 5 && argc != 6)
	{
		write(2, "Error\nTry : ./philo [number_of_philos] [time_to_die] \
			[time_to_eat] [time_to_sleep] [number_of_meals]", 104);
		return (1);
	}
	if (check_num(&table, argv) == 1)
		printf("Error");
	if (table.number_of_meals == 0)
		return 0;
	init_table(&table, philos);
	init_fork(&table, forks);
	init_philos(&table, forks);
	threads_create(&table, forks);
	monitoring();
}