/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/10 14:24:45 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/* PHILO
  *  run the program example
  * ./philo 5 800 200 200 [5]
  *	        
 */

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
    int id;
    pthread_t thread_id;
    t_fork	*left_fork;
    t_fork	*right_fork;
	long	meals_counter;
	bool	full;
	long	last_meal_time;
}			t_philo;

typedef struct s_data
{
    long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	start_simulation;
	long	num_limit_meals; // [5] 
	bool	end_simulation; // philos dies or philos all full
    t_philo	*philos;
    t_fork	*forks;
}			t_data;

/* FUNCTIONS PHILO */
void	start_simulation(t_data *data);
int		init_data(t_data *data, long num_philosophers);
void	*ft_philosopher_routine(void *arg);
void	cleanup(t_data *data);
void	precise_usleep(long usec);
