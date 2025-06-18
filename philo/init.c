/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:20:21 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:47:24 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->philos[i].id = i;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->nb_philo;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		i++;
	}
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (parse_args(argc, argv, table))
		return (2);
	table->finished = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (printf("Error: malloc failed\n"), 2);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (free(table->forks), printf("Error: malloc failed\n"), 2);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->finish_mutex, NULL);
	init_philos(table);
	return (0);
}
