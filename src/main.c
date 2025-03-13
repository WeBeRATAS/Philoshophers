/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:10:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/13 13:09:15 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


static void	free_table(t_table *table)
{
	int		i;

	i = -1;
	while (table->philos[++i])
		pthread_join(table->philos[i]->philo_thread, NULL);
	i = -1;
	while (table->philos[++i])
	{
		pthread_mutex_destroy(&table->philos[i]->left_fork);
		//pthread_mutex_destroy(&table->philos[i]->last_m);
		//pthread_mutex_destroy(&table->philos[i]->eating_m);
		free(table->philos[i]);
	}
	pthread_mutex_destroy(&table->stop_m);
	free (table->philos);
}

int	main(int ac, char **av)
{
	t_table	table;

	init_table(&table);
	if (!check_args(ac, av, &table))
	{
		printf("Wrong parametres \n");
        printf("Use %s <philos🎅> <die☠️ > <eat🍴> <sleep💤>[meals🍝]\n", av[0]);
        printf("Example: ./philo 6 200 200 200 [3]\n");
		if (table.philos)
			free(table.philos);
		return (1);
	}
	start_threads(&table);
	//usleep(50 * ac);
	philo_controller(&table, -1);
	free_table(&table);
	return (0);
}
