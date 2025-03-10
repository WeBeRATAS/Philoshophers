/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/10 18:27:47 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	t_philo			**philos;
	long long		tto_die;
	int				tto_eat;
	int				tto_sleep;
	int				each_eat;
	pthread_mutex_t	stop_m;
	bool			stop;
	long long		reset_time;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_thrd;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
	pthread_mutex_t	eating_m;
	bool			is_eating;
	int				name;
	int				meals;
	pthread_mutex_t	last_m;
	long long		last_meal;
}	t_philo;

//Main_Functions
bool		check_init_args(int ac, char **av, t_table *table);
void		set_forks(t_table *table);
void		*ft_routine_philosophers(void *arg);
void		start_threads(t_table *table);
long long	current_timestamp(void);
int			philo_killer(t_table *table, int i);
void		kill(t_table *table, int i);

//Philophers Actions
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);
void		precise_usleep(long miliseconds);

#endif
