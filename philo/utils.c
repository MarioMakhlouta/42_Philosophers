/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:48:22 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/12 12:35:58 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_action(t_philo *philo, char *action)
{
	int	done;

	pthread_mutex_lock(&philo->table->finish_mutex);
	done = philo->table->finished;
	pthread_mutex_unlock(&philo->table->finish_mutex);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!done)
		printf("%ld %d %s\n",
			get_time() - philo->table->start_time,
			philo->id + 1,
			action);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	msleep(philo->table->time_to_sleep);
}
