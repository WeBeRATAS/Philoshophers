/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:11:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 21:55:09 by rbuitrag         ###   ########.fr       */
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
	if (ac < 5 || ac > 6 || !check_digits(ac, av))
		return (false);
	table->tto_die = ft_atoi(av[2]);
	table->tto_eat = ft_atoi(av[3]);
	table->tto_sleep = ft_atoi(av[4]);
	table->each_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	table->num_philos = ft_atoi(av[1]);
	if (table->tto_die <= 0 || table->tto_eat <= 0 || 
		table->tto_sleep <= 0 || table->num_philos <= 0 || 
		(ac == 6 && table->each_eat <= 0))
		return (false);
	table->philos = malloc((table->num_philos + 1) * sizeof(t_philo *));
	if (!table->philos)
		return (false);
	table->philos[table->num_philos] = NULL;
	return (init_philosophers(table, table->num_philos), true);
}