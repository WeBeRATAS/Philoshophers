/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/18 21:42:00 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int philo_controller(t_table *table, int i)
{
    long	time_now;

    while (1)
    {
        pthread_mutex_lock(&table->stop_m);
        if (table->stop)
        {
            pthread_mutex_unlock(&table->stop_m);
            return (1);
        }
        pthread_mutex_unlock(&table->stop_m);

        i = 0;
        while (table->philos[i])
		{
			pthread_mutex_lock(&table->philos[i]->last_m);
            time_now = get_time_ml();
            printf("Philo %d last meal: %ld, time now: %ld, tto_die: %ld\n", 
                   i + 1, table->philos[i]->last_meal, time_now, table->tto_die);
            if (time_now - table->philos[i]->last_meal > table->tto_die)
            {
                pthread_mutex_unlock(&table->philos[i]->last_m);
                kill(table, i);
                return (1);
            }
            pthread_mutex_unlock(&table->philos[i]->last_m);
            i++;
        }
        usleep(1000); // 💤 Pequeña pausa para reducir uso de CPU
    }
    return (0);
}
