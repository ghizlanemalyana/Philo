/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:21:31 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/10 15:53:17 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_exit(t_table *table, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_detach(table->philos[i].thread);
		i++;
	}
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_destroy(&table->philos[i].lock);
		pthread_mutex_destroy(table->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_lock);
	pthread_mutex_destroy(&table->print_lock);
}

static int	full_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (table->number_of_meals == -1)
		return (0);
	while (i < table->number_of_philos)
	{
		philo = &table->philos[i];
		if (get_value(&philo->lock, &philo->meals_counter)
			!= table->number_of_meals)
			return (0);
		i++;
	}
	return (1);
}

static int	dead_philo(t_philo *philo)
{
	t_table	*table;
	long	res;

	table = philo->table;
	if (get_value(&philo->lock, &philo->last_meal_time) == 0)
		return (0);
	res = get_current_time() - get_value(&philo->lock, &philo->last_meal_time)
		>= table->time_to_die;
	if (res == 1)
	{
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

static void	monitoring(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (full_philo(table) || dead_philo(&table->philos[i]))
				return (my_exit(table, table->number_of_philos));
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (argc != 5 && argc != 6)
	{
		write(2, "Error\nTry : ./philo [number_of_philos] [time_to_die] "
			"[time_to_eat] [time_to_sleep] [number_of_meals]", 101);
		return (1);
	}
	if (check_num(&table, argv) == 1)
	{
		printf("Invalid input\n");
		return (1);
	}
	if (table.number_of_meals == 0)
		return (0);
	if (init_program(&table, philos, forks) == 1)
		return (1);
	if (threads_create(&table) == 1)
		return (1);
	monitoring(&table);
}
