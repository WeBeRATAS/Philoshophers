/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/18 13:38:06 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int philo_controller(t_table *table, int i)
{
    long	time_now;

    	i = -1;
		while (table->philos[++i] && !table->stop)
		{
			pthread_mutex_lock(&table->stop_m);
			if (!table->stop)
			{
				pthread_mutex_unlock(&table->stop_m);
				time_now = get_time_ml();
				if (table->philos[i]->last_meal != -1)
				{
					if (time_now - table->philos[i]->last_meal > table->tto_die)
					{
						kill(table, i);
						break ;
					}
				}
				else
				{
					if (time_now - table->reset_time > table->tto_die)
					{
						kill(table, i);
						break ;
					}
				}
			}
			else
				return(pthread_mutex_unlock(&table->stop_m));
		}
		return(pthread_mutex_unlock(&table->stop_m));
}