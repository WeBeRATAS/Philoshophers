/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:06:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/19 21:30:39 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */

void	*ft_routine_philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->right_fork == &philo->left_fork)
		return (NULL);
	if (philo->id % 2 == 0)
		precise_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->table->stop_m);
		if (philo->table->stop)
		{
			pthread_mutex_unlock(&philo->table->stop_m);
			break;
		}

		pthread_mutex_unlock(&philo->table->stop_m);

		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
		return (NULL);
}

