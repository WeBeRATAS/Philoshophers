/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:06:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 21:06:44 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] valgrid --tool=helgrind  */

void	*ft_routine_philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->right_fork == &philo->left_fork)
		return (NULL);
	pthread_mutex_lock(&philo->table->stop_m);
	while (!philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->stop_m);
		philo_eat(philo);
		pthread_mutex_lock(&philo->eating_m);
		philo->is_eating = false;
		pthread_mutex_unlock(&philo->eating_m);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->table->stop_m);
		if (philo->meals == philo->table->each_eat)
			break ;
	}
	pthread_mutex_unlock(&philo->table->stop_m);
	return (NULL);
}
