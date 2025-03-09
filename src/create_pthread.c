/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:39:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/09 11:16:02 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void start_simulation(t_data *data)
{
	int	i;

	i = 0;
    while (i < data->num_philo)
	{
		pthread_create(&data->philos[i].thread_id, NULL,
				ft_philosopher_routine, &data->philos[i]);
		i++;    
	}
	i = 0;
    while (i < data->num_philo)
       pthread_join(data->philos[i++].thread_id, NULL);
}
