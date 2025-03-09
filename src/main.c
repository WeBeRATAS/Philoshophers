/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:10:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/09 17:45:10 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long ft_atol(const char *str)
{
	long	i;
	long	is_neg;
	long	res;

	i = 0;
	is_neg = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i]     == '\r'
		 || str[i] == 32 || str[i] == '\v' || str[i] ==     '\f')
	 i++;
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] != '\0') && (str[i] >= '0' && str[i    ] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (is_neg)
		res *= -1;
	return (res);
}

int main(int ac, char **av)
{
    t_data data;
    
    if (ac < 5 || ac > 6)
    {
        printf("Uso: %s <philos> <die> <eat> <sleep> [meals]\n", av[0]);
        return (1);
    }
   // data = calloc(ft_atol(av[1]), sizeof(t_data));
    data.num_philo = ft_atol(av[1]);
    data.time_to_die = ft_atol(av[2]);
    data.time_to_eat = ft_atol(av[3]);
    data.time_to_sleep = ft_atol(av[4]);
    if (ac == 6)
        data.num_limit_meals = ft_atol(av[5]);
    if (data.num_philo <= 0 || data.time_to_die <= 0 
        || data.time_to_eat <= 0 || data.time_to_sleep <= 0 
        || (ac == 6 && data.num_limit_meals <= 0)) {
        printf("Error: Argumentos deben ser numeros positivos\n");
        return (1);
    }
    if (init_data(&data, data.num_philo) != 0) {
        printf("Error inicializando datos\n");
        return (1);
    }
    start_simulation(&data);
    cleanup(&data);
    return (0);
}
