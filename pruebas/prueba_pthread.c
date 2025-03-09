/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:02:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/03 09:10:53 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*thread_func( void *arg)
{

	(void)arg;
	printf ("Hola desde el hilo!!!!!\n");
	return (NULL);
}

int	main()
{
	pthread_t	thread_id;

	// Creamos nuevo hilo
	while (1)
	{
		if (pthread_create(&thread_id,NULL, thread_func, NULL) != 0)
		{
			perror ("Error al crear el hilo");
			return (1);
		}

		sleep(1);

		//pthread_join(thread_id, NULL);
		printf ("Saliendo de la main \n");
	}
	return (0);
}
