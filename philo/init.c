/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:42:36 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/03 05:45:55 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_table(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	table->start_time = 0;
	if (pthread_mutex_init(&table->table_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->table_lock);
		return (1);
	}
	return (0);
}

static void	destroy(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static int	init_forks(t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy(forks, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].l_fork = &forks[i];
		if (pthread_mutex_init(&table->philos[i].lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].lock);
			return (1);
		}
		if (i == 0)
			table->philos[i].r_fork = &forks[table->number_of_philos - 1];
		else
			table->philos[i].r_fork = &forks[i - 1];
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

int	init_program(t_table *table, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (init_table(table, philos) == 1)
		return (1);
	if (init_forks(table, forks) == 1)
	{
		pthread_mutex_destroy(&table->table_lock);
		pthread_mutex_destroy(&table->print_lock);
		return (1);
	}
	if (init_philos(table, forks) == 1)
	{
		pthread_mutex_destroy(&table->table_lock);
		pthread_mutex_destroy(&table->print_lock);
		destroy(forks, table->number_of_philos);
		return (1);
	}
	return (0);
}
