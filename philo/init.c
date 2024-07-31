/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:42:36 by gmalyana          #+#    #+#             */
/*   Updated: 2024/07/31 02:18:16 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	table->start_time = 0;
	// pthread_mutex_init(&table->table_lock, NULL);
	// pthread_mutex_init(&table->print_lock, NULL);
	// pthread_mutex_init(&table->meals_lock, NULL);
}
void	init_fork(t_table *table, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_table *table, pthread_mutex_t *forks)
{
	int i;
	i = 0;

	while (i < table->number_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].l_fork = &forks[i];
		pthread_mutex_init(&table->philos[i].lock, NULL); //!
		if (i == 0)
			table->philos[i].r_fork = &forks[table->number_of_philos - 1];
		else
			table->philos[i].r_fork = &forks[i - 1];
		i++;
	}
}