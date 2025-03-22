/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:12:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/22 08:55:46 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is sleeping 💤 \n", get_time_ml() \
				- philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_sleep);
}

void	philo_eat(t_philo *philo)
{
	if (philo->full)
		return ;
	if (!handle_forking(philo, philo->first_fork, philo->second_fork))
        return;
	//pthread_mutex_lock(&philo->table->stop_m);
	if (philo->table->stop)
	{
		drop_forks(philo);
		//pthread_mutex_unlock(&philo->table->stop_m);
		return ;
	}
	pthread_mutex_lock(&philo->table->stop_m);
	philo->last_meal = get_time_ml();
	philo->meals++;
	printf("%ld %d is eating 🍝\n", philo->last_meal \
			- philo->table->reset_time, philo->id);
	if (philo->table->each_eat == philo->meals)
		philo->full = true;
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(philo->table->tto_eat);
	drop_forks(philo);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_m);
	if (!philo->table->stop)
		printf ("%ld %d is thinking 🤔 \n", get_time_ml() \
				- philo->table->reset_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_m);
	precise_usleep(1);
}
