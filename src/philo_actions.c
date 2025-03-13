/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:12:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/13 13:57:13 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		precise_usleep(philo->table->tto_die);
		pthread_mutex_unlock(fork);
		return (false);
	}
	if (pthread_mutex_lock(fork))
		return (false);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d has taken a fork 🍴 [%p]\n", get_time_ml() - \
				philo->table->reset_time, philo->id, fork);
	pthread_mutex_unlock(&philo->table->stop_m);
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is sleeping 💤 \n", get_time_ml() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	
	if (philo->id % 2 == 0) // Para evitar deadlocks
	{
		if (!take_fork(&philo->left_fork, philo))
			return ;
		if (!take_fork(philo->right_fork, philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			return ;
		}
	}
	else
	{
		if (!take_fork(philo->right_fork, philo))
			return ;
		if (!take_fork(&philo->left_fork, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
	}
	pthread_mutex_lock(&philo->table->stop_m);
	pthread_mutex_unlock(&philo->table->stop_m);
	philo->meals++;
	philo->last_meal = get_time_ml();
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf("%ld %d is eating 🍝 \n", get_time_ml() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is thinking 🤔 \n", get_time_ml() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	//precise_usleep((philo->table->tto_eat / 2));
}