/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 20:58:18 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_forks(t_table *table)
{
	int	i;

	i = -1;
	while (table->philos[++i])
	{
		if (table->philos[i + 1])
			table->philos[i]->right_fork = &table->philos[i + 1]->left_fork;
		else
			table->philos[i]->right_fork = &table->philos[0]->left_fork;
	}
}

void	start_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->philos)
	{
		while (table->philos[++i])
		{
			table->philos[i]->last_meal = current_timestamp();
			pthread_create(&table->philos[i]->philo_thrd, NULL, \
				ft_routine_philosophers, table->philos[i]);
		}
	}
}

static void	unlock_and_gettime(t_table *table, long *time_now, int i)
{
	pthread_mutex_unlock(&table->stop_m);
	*time_now = current_timestamp();
	pthread_mutex_lock(&table->philos[i]->last_m);
}

static void	killer_func(t_table *table, int i)
{
	pthread_mutex_lock(&table->philos[i]->eating_m);
	if (!table->philos[i]->is_eating)
		kill(table, i);
	pthread_mutex_unlock(&table->philos[i]->eating_m);
	pthread_mutex_unlock(&table->philos[i]->last_m);
}

int philo_cleaner(t_table *table, int i)
{
    long	time_now;

    while (1)
	{
		i = -1;
		while (table->philos[++i])
		{
			pthread_mutex_lock(&table->stop_m);
			if (!table->stop)
			{
				unlock_and_gettime(table, &time_now, i);
				if (time_now - table->philos[i]->last_meal > table->tto_die)
				{
					killer_func(table, i);
					break ;
				}
				else
					pthread_mutex_unlock(&table->philos[i]->last_m);
			}
			else
				return (pthread_mutex_unlock(&table->stop_m));
		}
	}
}