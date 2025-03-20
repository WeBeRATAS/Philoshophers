/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 22:03:40 by rbuitrag         ###   ########.fr       */
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

void	kill(t_table *table, int i, long time_now)
{
	table->stop = true;
	precise_usleep(2);
	printf("%ld %d died ☠️  \n", time_now - table->reset_time, i + 1);
}

