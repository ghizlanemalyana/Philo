/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:46 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/04 01:19:00 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_number(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (str[i] == '\0')
		return (-2);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (res > INT_MAX || str[i] != '\0')
		return (-2);
	return (res);
}

int	check_num(t_table *table, char **args)
{
	table->number_of_philos = get_number(args[1]);
	table->time_to_die = get_number(args[2]);
	table->time_to_eat = get_number(args[3]);
	table->time_to_sleep = get_number(args[4]);
	table->number_of_meals = -1;
	if (args[5] != NULL)
		table->number_of_meals = get_number(args[5]);
	if (table->number_of_philos < 1 || table->number_of_philos > 200
		|| table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60 || table->number_of_meals == -2)
		return (1);
	return (0);
}
