/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:12:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 14:09:25 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d has taken a fork 🍴 \n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d is sleeping 💤 \n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_eat / 2);
}

void	philo_eat(t_philo *philo)
{
	if (&philo->left_fork < philo->right_fork)
	{
		take_fork(&philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(&philo->left_fork, philo);
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
		printf ("%lld %d is eating 🍝 \n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%lld %d is thinking 🤔 \n", current_timestamp() - \
				philo->table->reset_time, philo->name);
	pthread_mutex_unlock(&philo->table->stop_m);
}
