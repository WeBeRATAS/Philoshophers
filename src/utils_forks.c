/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:47:43 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/21 18:11:13 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	if (pthread_mutex_lock(fork) != 0)
		return (false);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d has taken a fork 🍴 \n", get_time_ml() \
				- philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	return (true);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

bool	handle_forking(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	if (!take_fork(first, philo))
	{
		pthread_mutex_unlock(second);
		return (false);
	}
	if (!take_fork(second, philo))
		return (false);
	return (true);
}
void	order_forking(t_philo *philo)
{
	if (philo->id % 2 == 0) 
    {
        philo->first_fork = philo->right_fork;
        philo->second_fork = &philo->left_fork;
    } 
    else 
    {
		philo->first_fork = &philo->left_fork;
        philo->second_fork = philo->right_fork;
    }
}
