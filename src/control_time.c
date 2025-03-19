/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/19 11:34:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


long	get_time_ml(void)
{
	struct	timeval	time;
	long	miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (miliseconds);
}

static long	gettmstmp(long start)
{
	return (get_time_ml() - start);
}

void	precise_usleep(long miliseconds)
{
	long	start_time;
	long	elapsed;

	start_time = get_time_ml();
	elapsed = gettmstmp(start_time);
	while (miliseconds > elapsed)
	{
		usleep(500);
		elapsed = gettmstmp(start_time);
	}
}

void	kill(t_table *table, int i)
{
    long	now;

    pthread_mutex_lock(&table->stop_m);
    table->stop = true;
    pthread_mutex_unlock(&table->stop_m);
    now = get_time_ml();
    pthread_mutex_lock(&table->philos[i]->last_m);
    if (table->each_eat != table->philos[i]->meals)
        printf("%ld %d died ☠️  \n", now - table->reset_time, i + 1);
    pthread_mutex_unlock(&table->philos[i]->last_m);
}

