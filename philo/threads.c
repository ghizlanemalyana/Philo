/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:29:42 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/10 15:32:39 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_create(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
		{
			set_value(&table->table_lock, &table->start_time, -1);
			my_exit(table, i);
		}
		i++;
	}
	set_value(&table->table_lock, &table->start_time, get_current_time());
}
