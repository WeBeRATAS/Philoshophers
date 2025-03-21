/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/21 20:15:13 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_full(t_table *table)
{
	if (table->total_full == table->num_philos)
	{
		pthread_mutex_unlock(&table->stop_m);
		return (1);
	}
	return (0);
}

void	philo_controller(t_table *table)
{
	long	time_now;
	int		i;

	i = 0;
	while (simulation(table))
	{
		pthread_mutex_lock(&table->stop_m);
		time_now = get_time_ml();
		if (check_full(table))
			return ;
		if (time_now - table->philos[i]->last_meal >= table->tto_die)
		{
			kill(table, i, time_now);
			pthread_mutex_unlock(&table->stop_m);
			return ;
		}
		pthread_mutex_unlock(&table->stop_m);
		i++;
		if (i == table->num_philos)
			i = 0;
		}
}
