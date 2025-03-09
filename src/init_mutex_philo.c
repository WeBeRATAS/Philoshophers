/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:41:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/09 14:56:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	cleanup(t_data *data)
{
	long	i;

	if (!data)
		return ;
	i = 0;
	if (data->forks)
	{
		while(i < data[i].num_philo)
		{
			pthread_mutex_destroy(&data->forks[i].fork);
			i++;
		}
	}
	free(data->forks);
    data->forks = NULL;
	if (data->philos)
	{
        free(data->philos);
    	data->philos = NULL;
    }
}

int init_data(t_data *data, long num_philo)
{
	long	i;
	t_data	*tmp;

    tmp = data;
	if (num_philo <= 0)
		return (-1);
	if (tmp)
		return (cleanup(data), -1);
	tmp->num_philo = num_philo;
    tmp->philos = malloc(sizeof(t_philo) * num_philo);
    if(!tmp->philos)
		return (-1);
	tmp->forks = malloc(sizeof(t_fork) * num_philo);
	if (!tmp->forks)
		return (free(tmp->philos), -1);
	i = 0;
    while (i < num_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
      	  // Destruir mutexes creados antes del error
        	while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].fork);
        	free(data->philos);
        	free(data->forks);
        	return (-1);
    	}
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		tmp->philos[i].id = i;
		tmp->philos[i].left_fork = &tmp->forks[i];
		tmp->philos[i].right_fork =
			&tmp->forks[(i + 1) % num_philo];
		i++;
    }
	return (0);
}
