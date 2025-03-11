/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:11:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 21:00:55 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

static void	init_philosophers(t_table *table, int num_philos)
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
		table->philos[i]->id = i;
		table->philos[i]->meals = 0;
		table->philos[i]->last_meal = -1;
		table->philos[i]->is_eating = false;
	}
	set_forks(table);
}

static bool	check_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++i < ac -1)
	{
		j = 0;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
		}
	}
	return (true);
}

bool	check_args(int ac, char **av, t_table *table)
{
	int	num;

	num = 0;
	if (!check_digits(ac, av))
		return (false);
	if (ac < 5 || ac > 6)
		return (false);
	if (ac == 6)
	{
		table->each_eat = ft_atoi(av[5]);
		if (table->each_eat <= 0)
			return (false);
	}
	table->tto_sleep = ft_atoi(av[4]);
	table->tto_eat = ft_atoi(av[3]);
	table->tto_die = ft_atoi(av[2]);
	num = ft_atoi(av[1]);
	if (!(table->tto_sleep > 0 && table->tto_eat > 0 && table->tto_die > 0 \
		&& num > 0))
		return (false);
	table->philos = malloc((num + 1) * sizeof(t_philo *));	
	table->philos[num] = NULL;
	if (!table->philos)
		return (false);
	init_philosophers(table, num);
	return (true);
}
