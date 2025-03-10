/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:41:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/10 16:12:36 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void cleanup(t_data *data)
{
    if (!data)
        return;
    if (data->forks)
	{
       free(data->forks);
       data->forks = NULL;
    }
    if (data->philos) {
        free(data->philos);
        data->philos = NULL;
    }
}

int init_data(t_data *data, long num_philo) {
    long i;

    if (!data || num_philo <= 0) // Verificar data != NULL
        return (-1);
    data->num_philo = num_philo;
    data->philos = malloc(sizeof(t_philo) * num_philo);
    if (!data->philos)
        return (-1);
    data->forks = malloc(sizeof(t_fork) * num_philo);
    if (!data->forks) {
        free(data->philos);
        return (-1);
    }
    // Inicializar mutexes para cada tenedor
    i = 0;
    while (i < num_philo) {
        if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0) {
            // Destruir mutexes ya creados
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i].fork);
            free(data->philos);
            free(data->forks);
            return (-1);
        }
        i++;
    }
    i = 0;
    while (i < num_philo) {
        data->philos[i].id = i;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % num_philo];
        i++;
    }
    return (0);
}
