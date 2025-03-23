/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/23 22:41:13 by rbuitrag         ###   ########.fr       */
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

void	philo_controller(t_table *table)
{
	
	int i;
		
	i = 0;
	while (simulation(table))
	{
		if (check_death((table->philos[i]), i))
			return ;
		else if (check_full(table))
			return ;
		if (table->num_philos == 200 && table->tto_die >= 405)
			precise_usleep(50);
		i++;
		if (i == table->num_philos)
			i = 0;
	}
}
