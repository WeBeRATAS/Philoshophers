/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:44 by rbuitrag          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/24 20:01:41 by rbuitrag         ###   ########.fr       */
=======
/*   Updated: 2025/03/24 11:00:21 by rbuitrag         ###   ########.fr       */
>>>>>>> 43c807a30467ca48e823cdce39aef1721112f3a6
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

void	precise_usleep(long milliseconds)
{
<<<<<<< HEAD
	long    start_time;
	long    elapsed;
	long    remaining;
	
=======
	long	start_time;
	long	elapsed;
	long	remaining;

>>>>>>> 43c807a30467ca48e823cdce39aef1721112f3a6
	start_time = get_time_ml();
	elapsed = 0;
	while (elapsed < milliseconds)
	{
<<<<<<< HEAD
	    remaining = milliseconds - elapsed;
	    if (remaining > 1)
		    usleep(remaining * 500);
	    else
		    usleep(200);
	    elapsed = get_time_ml() - start_time;
=======
		remaining = milliseconds - elapsed;
		if (remaining > 1)
			usleep(remaining * 500);
		else
			usleep(200);
		elapsed = get_time_ml() - start_time;
>>>>>>> 43c807a30467ca48e823cdce39aef1721112f3a6
	}
}

void	kill(t_table *table, int i, long time_now)
{
	table->stop = true;
	printf("%ld %d died ☠️  \n", time_now - table->reset_time, i + 1);
}
