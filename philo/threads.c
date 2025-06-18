/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:22:31 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/10 12:59:37 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread,
				NULL, philo_routine, &table->philos[i]))
		{
			printf("Error: pthread_create failed\n");
			destroy_table(table);
			return (2);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			printf("Error: Failed to join thread %d\n", i);
		i++;
	}
}
