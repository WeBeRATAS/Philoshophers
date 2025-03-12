/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:12:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/12 13:45:06 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d has taken a fork 🍴 [%p]\n", current_timestamp() - \
				philo->table->reset_time, philo->id, fork);
	if (philo->table->num_philos == 1)
	{
		precise_usleep(philo->table->tto_die);
		pthread_mutex_unlock(fork);
		return (false);
	}
	pthread_mutex_unlock(&philo->table->stop_m);
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is sleeping 💤 \n", current_timestamp() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	if (!take_fork(&philo->left_fork, philo))
		return ;
	if (!take_fork(philo->right_fork, philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return ;		
	}
	pthread_mutex_lock(&philo->eating_m);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->eating_m);
	pthread_mutex_lock(&philo->last_m);
	philo->meals++;
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(&philo->last_m);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is eating 🍝 \n", current_timestamp() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is thinking 🤔 \n", current_timestamp() - \
				philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep((philo->table->tto_eat / 2));
}
