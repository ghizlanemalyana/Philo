/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:23:51 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/10 15:32:11 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define THINK "%ld %d is thinking\n"
# define EAT "%ld %d is eating\n"
# define SLEEP "%ld %d is sleeping\n"
# define DIE "%ld %d dead\n"
# define HOLD_FORK "%ld %d has taken a fork\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_table			*table;
}	t_philo;

struct s_table
{
	long			number_of_philos;
	long			number_of_meals;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	print_lock;
	long			start_time;
	long			dead_flag;
	t_philo			*philos;
};

void	*philo_routine(void *ptr);
long	get_current_time(void);
int		get_number(char *str);
int		check_num(t_table *s, char **args);
long	get_value(pthread_mutex_t *mutex, long *variable);
void	set_value(pthread_mutex_t *mutex, long *variable, long value);
void	threads_create(t_table *table);
void	my_usleep(t_table *table, long time);
long	get_current_time(void);
void	print(t_philo *philo, char *str);
int		init_program(t_table *table, t_philo *philos, pthread_mutex_t *forks);
void	my_exit(t_table *table, int num);

#endif
