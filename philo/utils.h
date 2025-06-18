/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakhlou <mmakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:48:32 by mmakhlou          #+#    #+#             */
/*   Updated: 2025/06/12 12:36:13 by mmakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

int		ft_atoi(const char *str);
long	get_time(void);
void	msleep(long ms);
void	print_action(t_philo *philo, char *action);
void	sleep_and_think(t_philo *philo);

#endif
