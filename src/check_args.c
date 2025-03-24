/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:11:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/24 19:56:01 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atoi(const char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		if (num > (INT_MAX / 10) || (num == (INT_MAX / 10) \
					&& (str[i] - '0') > (INT_MAX % 10)))
			return (-1);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (num == 0)
		return (-1);
	return (num);
}

static bool	is_valid_number(const char *str)
{
	if (ft_atoi(str) == -1)
		return (false);
	return (true);
}

bool	check_args(int ac, char **av, t_table *table)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (false);
		i++;
	}
	table->num_philos = ft_atoi(av[1]);
	table->tto_die = ft_atoi(av[2]);
	table->tto_eat = ft_atoi(av[3]);
	table->tto_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->each_eat = ft_atoi(av[5]);
	else
		table->each_eat = -1;
	table->philos = malloc((table->num_philos + 1) * sizeof(t_philo *));
	if (!table->philos)
		return (false);
	table->philos[table->num_philos] = NULL;
	init_philosophers(table, table->num_philos);
	return (true);
}
