/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 12:20:08 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	precise_usleep(long miliseconds)
{
	long long	start_time;
	long long	elapsed;

	start_time = current_timestamp();
	elapsed = current_timestamp() - start_time;
	while (miliseconds > elapsed)
	{
		usleep(100);
		elapsed = current_timestamp() - start_time;
	}
}

void	kill(t_table *table, int i)
{
	long long	now;

	pthread_mutex_lock(&table->stop_m);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_m);
	now = current_timestamp();
	if (table->each_eat != table->philos[i]->meals)
		printf("%lld %d died ☠️  \n", now - table->reset_time, i + 1);
}
