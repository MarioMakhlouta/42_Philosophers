/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:45:03 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/13 10:46:07 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	print_action(philo, "is thinking");
	if (table->nb_philo == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	philo_loop(philo);
	return (NULL);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"), 2);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	if (table->nb_philo < 1 || table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || (argc == 6 && table->must_eat < 1))
		return (printf("Error: invalid argument\n"), 2);
	return (0);
}

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->finish_mutex);
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"), 2);
	if (parse_args(argc, argv, &table))
		return (2);
	table.start_time = get_time();
	if (init_table(&table, argc, argv))
	{
		destroy_table(&table);
		return (2);
	}
	if (create_threads(&table))
		return (1);
	usleep(100);
	if (monitor(&table))
	{
		join_threads(&table);
		destroy_table(&table);
		return (0);
	}
	if (table.nb_philo != 1)
		join_threads(&table);
	destroy_table(&table);
	return (0);
}
