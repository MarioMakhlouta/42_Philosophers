/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:19:08 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:51:59 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

int	try_take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_action(philo, "has taken a fork");
	return (1);
}

void	release_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!try_take_forks(philo))
		return ;
	print_action(philo, "is eating");
	update_meal_time(philo);
	msleep(table->time_to_eat);
	release_forks(philo);
}

void	philo_loop(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id % 2)
		msleep(30);
	while (!is_finished(table))
	{
		eat(philo);
		if (is_finished(table))
			break ;
		print_action(philo, "is sleeping");
		msleep(table->time_to_sleep);
		print_action(philo, "is thinking");
	}
}
