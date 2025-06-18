/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:17:38 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:47:03 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	is_finished(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->finish_mutex);
	result = table->finished;
	pthread_mutex_unlock(&table->finish_mutex);
	return (result);
}

int	check_philo_death(t_table *table, int i)
{
	long	time_since_last_meal;
	int		code;

	code = 0;
	pthread_mutex_lock(&table->philos[i].meal_mutex);
	time_since_last_meal = get_time() - table->philos[i].last_meal;
	pthread_mutex_unlock(&table->philos[i].meal_mutex);
	if (time_since_last_meal >= table->time_to_die)
	{
		pthread_mutex_lock(&table->finish_mutex);
		if (!table->finished)
		{
			table->finished = 1;
			pthread_mutex_unlock(&table->finish_mutex);
			pthread_mutex_lock(&table->print_mutex);
			printf("%ld %d died\n",
				get_time() - table->start_time,
				table->philos[i].id + 1);
			pthread_mutex_unlock(&table->print_mutex);
			code = 1;
		}
		else
			pthread_mutex_unlock(&table->finish_mutex);
	}
	return (code);
}

int	check_and_update_eat_status(t_table *table, int i, int *done)
{
	if (check_philo_death(table, i))
		return (1);
	if (table->must_eat > 0)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten < table->must_eat)
			*done = 0;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
	}
	return (0);
}

int	monitor_loop(t_table *table, int *code)
{
	int	i;
	int	done;

	i = -1;
	done = 1;
	while (++i < table->nb_philo)
	{
		if (check_and_update_eat_status(table, i, &done))
		{
			*code = 1;
			return (1);
		}
	}
	if (table->must_eat > 0 && done)
	{
		pthread_mutex_lock(&table->finish_mutex);
		table->finished = 1;
		pthread_mutex_unlock(&table->finish_mutex);
	}
	return (0);
}

int	monitor(t_table *table)
{
	int	code;

	code = 0;
	while (!is_finished(table))
	{
		if (monitor_loop(table, &code))
			break ;
		usleep(1000);
	}
	return (code);
}
