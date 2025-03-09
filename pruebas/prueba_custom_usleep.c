/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_custom_usleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:31:22 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/03 13:01:53 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#define BOL_RED "\033[1;31m"
#define RESET "\033[0m"

long get_elapsed_ms(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec -
			start.tv_usec);
}

void precise_usleep(long usec)
{
	struct timeval start, current;
	long elapsed;
	long rem;

	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_ms(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

int	main(void)
{
	struct timeval start;
	struct timeval end;
	long seconds;
	long microseconds;
	double elapsed;

	gettimeofday(&start, NULL);
	precise_usleep(5000000);
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds * 1e-6;

	/*printf("Expected sleeep: " BOLD_RED "\t0.5" RESET " seconds \n");
	printf("Actual sleeep: " BOLD_RED "\t\t%f" RESET " seconds \n\n",
	elapsed);*/
	printf("Expected sleep duration: \t %ld \n", seconds);
    printf("Actual sleep duration: \t\t %ld %f \n\n", seconds, elapsed);
	return (0);
}

