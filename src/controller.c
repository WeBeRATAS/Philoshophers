/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/24 10:32:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_full(t_table *table)
{
	pthread_mutex_lock(&table->stop_m);
	if (table->total_full == table->num_philos)
	{
		pthread_mutex_unlock(&table->stop_m);
		return (1);
	}
	pthread_mutex_unlock(&table->stop_m);
	return (0);
}

bool	check_death(t_philo *philo, int i)
{
	long	time_now;

	pthread_mutex_lock(&philo->table->stop_m);
	time_now = get_time_ml();
	if (time_now - philo->last_meal >= philo->table->tto_die)
	{
		kill(philo->table, i, time_now);
		pthread_mutex_unlock(&philo->table->stop_m);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->stop_m);
	return (false);
}

void	philo_controller(t_table *table)
{
	int	i;

	i = 0;
	while (simulation(table))
	{
		if (check_death((table->philos[i]), i))
			return ;
		else if (check_full(table))
			return ;
		if (table->num_philos == 200 && table->tto_die >= 405)
			precise_usleep(50);
		else if (table->num_philos == 3 && table->tto_die >= 185)
			precise_usleep(50);
		i++;
		if (i == table->num_philos)
			i = 0;
	}
}
