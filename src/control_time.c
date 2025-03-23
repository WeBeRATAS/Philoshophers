/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/23 22:38:15 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time_ml(void)
{
	struct timeval	time;
	long			miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (miliseconds);
}

void    precise_usleep(long milliseconds)
{
    long    start_time;
    long    elapsed;
    long    remaining;

    start_time = get_time_ml();
    elapsed = 0;
    while (elapsed < milliseconds)
    {
        remaining = milliseconds - elapsed;
        if (remaining > 1)
            usleep(remaining * 500);
        else
            usleep(200);
        elapsed = get_time_ml() - start_time;
    }
}

void	kill(t_table *table, int i, long time_now)
{
	table->stop = true;
	printf("%ld %d died ☠️  \n", time_now - table->reset_time, i + 1);
}
