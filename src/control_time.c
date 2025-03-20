/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 21:15:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


long	get_time_ml(void)
{
	struct	timeval	time;
	long long	miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = time.tv_sec * 1000LL + time.tv_usec / 1000LL;
	return (miliseconds);
}

static long	gettmstmp(long long start)
{
	return (get_time_ml() - start);
}

void	precise_usleep(long long miliseconds)
{
	long long	start_time;
	long long	elapsed;

	start_time = get_time_ml();
	elapsed = gettmstmp(start_time);
	while (miliseconds > elapsed)
	{
		usleep(500);
		elapsed = gettmstmp(start_time);
	}
}

void	kill(t_table *table, int i, long long now)
{
	pthread_mutex_lock(&table->stop_m);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_m);
	pthread_mutex_lock(&table->philos[i]->last_m);
	if (table->each_eat != table->philos[i]->meals)
		printf("%lld %d died ☠️\n", now - table->reset_time, i + 1);
	pthread_mutex_unlock(&table->philos[i]->last_m);
}


