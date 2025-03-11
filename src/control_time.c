/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 20:54:42 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	current_timestamp(void)
{
	struct	timeval	time;
	long	milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000 + (time.tv_usec / 1000);
	return (milliseconds);
}

void	precise_usleep(long miliseconds)
{
	long start_time;
	long elapsed;

	start_time = current_timestamp();
	elapsed = current_timestamp() - start_time;
	while (miliseconds > elapsed)
	{
		usleep(200);
		elapsed = current_timestamp() - start_time;
	}
}

void	kill(t_table *table, int i)
{
	long	now;

	pthread_mutex_lock(&table->stop_m);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_m);
	now = current_timestamp();
	if (table->each_eat != table->philos[i]->meals)
		printf("%ld %d died ☠️  \n", now - table->reset_time, i + 1);
}
