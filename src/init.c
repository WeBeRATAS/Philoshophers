/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:06:52 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 21:07:03 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_table(t_table *table)
{
	table->each_eat = -1;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->philos = NULL;
	table->stop = false;
	table->reset_time = current_timestamp();
	pthread_mutex_init(&table->stop_m, NULL);
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
