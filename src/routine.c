/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:06:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/19 20:13:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */

bool simulation(t_table *table)
{
  pthread_mutex_lock(&table->stop_m);
  if (table->stop)
  {
    pthread_mutex_unlock(&table->stop_m);
    return (false);
  }
  pthread_mutex_unlock(&table->stop_m);
  return (true);
}

void	*ft_routine_philosophers(void *arg)
{
	t_philo	*philo;
	long time_since_last_meal;
	long time_to_next_action;


	philo = (t_philo *)arg;
	if (philo->right_fork == &philo->left_fork)
		return (NULL);
	if (philo->id % 2 == 0)
    precise_usleep(1);
	while (simulation(philo->table))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
    pthread_mutex_lock(&philo->table->stop_m);
		if (philo->meals == philo->table->each_eat && philo->table->each_eat != -1)
    {
      philo->full = true;
      philo->table->total_full++;
      pthread_mutex_unlock(&philo->table->stop_m);
			break ;
    }
    pthread_mutex_unlock(&philo->table->stop_m);
    // Calcular el tiempo hasta la próxima acción
        time_since_last_meal = get_time_ml() - philo->last_meal;
        time_to_next_action = philo->table->tto_eat - time_since_last_meal;

        // Dormir solo si es necesario
        if (time_to_next_action > 0)
            precise_usleep(time_to_next_action);
	}
	return (NULL);
}
