/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:52 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/10 14:33:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *ft_philosopher_routine(void *arg)
{
    t_philo *philo;

	philo = (t_philo *)arg;

		// Pensar
		printf("Filosofo %d esta pensando.🤔\n", philo->id);
		precise_usleep(200);
		// Tomar los tenedores
		pthread_mutex_lock(&(philo->left_fork->fork));
		pthread_mutex_lock(&(philo->right_fork->fork));
		// Comer
		printf("Filosofo %d esta comiendo.🍴\n", philo->id);
		precise_usleep(200);
		// Soltar los tenedores
		pthread_mutex_unlock(&(philo->left_fork->fork));
		pthread_mutex_unlock(&(philo->right_fork->fork));
		// Dormir
		printf("Filosofo %d esta durmiendo.💤\n", philo->id);
		precise_usleep(200);
 
	return (NULL);
}
