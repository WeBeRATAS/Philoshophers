/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:52 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/09 12:50:19 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *ft_philosopher_routine(void *arg)
{
    t_philo *philo;

	philo = (t_philo *)arg;

		// Pensar
		printf("Filósofo %d está pensando.\n", philo->id);
		usleep(2000);
		// Tomar los tenedores
		pthread_mutex_lock(&(philo->left_fork->fork));
		pthread_mutex_lock(&(philo->right_fork->fork));
		// Comer
		printf("Filósofo %d está comiendo.\n", philo->id);
		usleep(2000);
		// Soltar los tenedores
		pthread_mutex_unlock(&(philo->left_fork->fork));
		pthread_mutex_unlock(&(philo->right_fork->fork));
		// Dormir
		printf("Filósofo %d está durmiendo.\n", philo->id);
		usleep(2000);
 
	return (NULL);
}
