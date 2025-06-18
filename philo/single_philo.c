/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:35:00 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:44:39 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	handle_single_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	update_meal_time(philo);
	while (!is_finished(table)
		&& (get_time() - philo->last_meal) < table->time_to_die)
		usleep(100);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
}
