/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:47:12 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/03 12:26:19 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

int main()
{
	struct timeval start, end;

	gettimeofday (&start, NULL);
	usleep (40000);
	gettimeofday (&end, NULL);

	long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;

	double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

	while (1)
	{
		printf ("Duracion suspension esperada: " BOLD_CYAN "\t500 ms\n" RESET);
		printf ("Duracion suspension real: " BOLD_CYAN "\t\t%.2f ms\n" RESET,
			elapsedMilliseconds);
		//sleep(1);
	}
	return (0);
}
