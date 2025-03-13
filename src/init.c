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
	table->reset_time = get_time_ml();
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
			table->philos[i]->last_meal = get_time_ml();
			pthread_create(&table->philos[i]->philo_thread, NULL, \
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

void	init_philosophers(t_table *table, int num_philos)
{
	int		i;

	i = -1;
	while (++i < num_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return ;
		pthread_mutex_init(&table->philos[i]->left_fork, NULL);
		pthread_mutex_init(&table->philos[i]->last_m, NULL);
		pthread_mutex_init(&table->philos[i]->eating_m, NULL);
		table->philos[i]->right_fork = NULL;
		table->philos[i]->table = table;
		table->philos[i]->id = i + 1;
		table->philos[i]->meals = 0;
		table->philos[i]->last_meal = -1;
		table->philos[i]->is_eating = false;
	}
	set_forks(table);
}