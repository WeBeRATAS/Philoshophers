/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 14:10:10 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int philo_controller(t_table *table, int i)
{
    long time_now;

    i = 0;
    while (simulation(table))
    {
        pthread_mutex_lock(&table->stop_m);
        time_now = get_time_ml();

        if (i >= table->num_philos)
        {
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        if (time_now - table->philos[i]->last_meal >= table->tto_die)
        //if (!table->philos[i]->full && time_now - table->philos[i]->last_meal >= table->tto_die)
        {
            kill(table, i, time_now);
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        if (table->total_full == table->num_philos)
        {
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        pthread_mutex_unlock(&table->stop_m);

        i++;
        if (i == table->num_philos)
            i = 0;
    }
    return (0);
}
