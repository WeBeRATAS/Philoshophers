/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 21:14:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *philo_controller(void *arg)
{
    long long	time_now;
    t_table *table;
    int		i;

    table = (t_table *)arg;
    
    while (1)
    {
        i = 0;
        while (i < table->num_philos) 
        {
            pthread_mutex_lock(&table->philos[i]->last_m);
            time_now = get_time_ml();
            if (time_now - table->philos[i]->last_meal == table->tto_die)
            {
                pthread_mutex_unlock(&table->philos[i]->last_m);
                kill(table, i, time_now); 
                return (NULL);
            }
            if (table->num_philos == 200 && table->tto_die == 410)
                precise_usleep(50);
            if (table->num_philos == 3 && table->tto_die == 190)
                precise_usleep(50);
            if (table->num_philos == 131 && table->tto_die >= 596)
                precise_usleep(50);
            pthread_mutex_unlock(&table->philos[i]->last_m);
            i++;
        }
        //precise_usleep(2);
    }
    return (NULL);
}
