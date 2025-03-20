/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 20:42:05 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void philo_controller(t_table *table)
{
    long time_now;
    int  i;

    i = 0;
    while (simulation(table))
    {
        pthread_mutex_lock(&table->stop_m);
        time_now = get_time_ml();

        if (table->total_full == table->num_philos)
        {
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        if (time_now - table->philos[i]->last_meal >= table->tto_die)
        {
            kill(table, i, time_now);
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        pthread_mutex_unlock(&table->stop_m);

        i++;
        if (i == table->num_philos)
            i = 0;
    }
}
