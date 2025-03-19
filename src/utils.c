/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/19 19:46:49 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int philo_controller(t_table *table, int i)
{
    long time_now;

    i = 0;
    while (1)
    {
        pthread_mutex_lock(&table->stop_m);
        time_now = get_time_ml();

        // Verificar si el índice i está dentro de los límites
        if (i >= table->num_philos)
        {
            pthread_mutex_unlock(&table->stop_m);
            break;  // Salir del bucle si i está fuera de los límites
        }
        if (!table->philos[i]->full && time_now - table->philos[i]->last_meal > table->tto_die)
        {
            kill(table, i, time_now);
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        else if (table->total_full == table->num_philos)
        {
            pthread_mutex_unlock(&table->stop_m);
            break;
        }
        pthread_mutex_unlock(&table->stop_m);

        // Incrementar i y asegurarse de que esté dentro de los límites
        i++;
        if (i == table->num_philos)
            i = 0;
    }
    return (0);
}
