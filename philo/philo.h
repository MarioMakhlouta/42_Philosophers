/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:45:30 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:51:59 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

// Philosopher and table structures
typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				finished;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
}	t_table;

// philo.c
void	*philo_routine(void *arg);
int		parse_args(int argc, char **argv, t_table *table);
void	destroy_table(t_table *table);

// routine.c
void	eat(t_philo *philo);
void	update_meal_time(t_philo *philo);
void	philo_loop(t_philo *philo);
int		try_take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

// monitor.c
int		is_finished(t_table *table);
int		check_philo_death(t_table *table, int i);
int		monitor(t_table *table);

// init.c
int		init_table(t_table *table, int argc, char **argv);
void	init_philos(t_table *table);

// threads.c
int		create_threads(t_table *table);
void	join_threads(t_table *table);

// single_philo.c
void	handle_single_philo(t_philo *philo);

#endif
