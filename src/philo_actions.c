/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:12:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 21:15:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool take_fork(pthread_mutex_t *fork, t_philo *philo)
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
        printf ("%lld %d has taken a fork 🍴 \n", get_time_ml() - philo->table->reset_time, philo->id);
    pthread_mutex_unlock(&philo->table->stop_m);
    return (true);
}

void philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->stop_m);
    if (!philo->table->stop)
        printf ("%lld %d is sleeping 💤 \n", get_time_ml() - philo->table->reset_time, philo->id);
    pthread_mutex_unlock(&philo->table->stop_m);
    precise_usleep(philo->table->tto_sleep);
}

void philo_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
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
    pthread_mutex_lock(&philo->last_m);
    philo->last_meal = get_time_ml();
    philo->meals++;
    pthread_mutex_unlock(&philo->last_m);
    if (philo->meals == philo->table->each_eat)
        philo->is_full = true;
    pthread_mutex_lock(&philo->table->stop_m);
    if (!philo->table->stop)
        printf("%lld %d is eating 🍝 \n", get_time_ml() - philo->table->reset_time, philo->id);
    pthread_mutex_unlock(&philo->table->stop_m);
    precise_usleep(philo->table->tto_eat);
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    
}

void philo_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->stop_m);
    if (!philo->table->stop)
        printf ("%lld %d is thinking 🤔 \n", get_time_ml() - philo->table->reset_time, philo->id);
    pthread_mutex_unlock(&philo->table->stop_m);
    //precise_usleep(1);
}
