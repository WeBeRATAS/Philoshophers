/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:06:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/24 19:57:11 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */

bool	simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_m);
	if (table->stop)
	{
		pthread_mutex_unlock(&table->stop_m);
		return (false);
	}
	pthread_mutex_unlock(&table->stop_m);
	return (true);
}
<<<<<<< HEAD

bool	check_death(t_philo *philo, int i)
{
	long time_now;
	
	pthread_mutex_lock(&philo->table->stop_m);
	time_now = get_time_ml();
	if (time_now - philo->last_meal >= philo->table->tto_die)
	{
		kill(philo->table, i, time_now);
		pthread_mutex_unlock(&philo->table->stop_m);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->stop_m);
	return (false);
}
=======
>>>>>>> 43c807a30467ca48e823cdce39aef1721112f3a6

void	*ft_routine_philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->right_fork == &philo->left_fork \
		|| philo->table->num_philos == 1)
		return (NULL);
	if (philo->id % 2 == 0)
<<<<<<< HEAD
		precise_usleep(1);
=======
		precise_usleep(0.1);
>>>>>>> 43c807a30467ca48e823cdce39aef1721112f3a6
	while (simulation(philo->table))
	{
		philo_eat(philo);
		pthread_mutex_lock(&philo->table->stop_m);
		if (philo->full)
		{
			philo->table->total_full++;
			pthread_mutex_unlock(&philo->table->stop_m);
			break ;
		}
		pthread_mutex_unlock(&philo->table->stop_m);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
