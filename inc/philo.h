/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/11 21:54:20 by rbuitrag         ###   ########.fr       */
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
	int				num_philos;
	long			tto_die;
	int				tto_eat;
	int				tto_sleep;
	int				each_eat;
	pthread_mutex_t	stop_m;
	bool			stop;
	long			reset_time;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	t_table			*table;
	pthread_t		philo_thrd;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	eating_m;
	bool			is_eating;
	pthread_mutex_t	last_m;
	long			last_meal;
}	t_philo;

//Main_Functions
bool		check_args(int ac, char **av, t_table *table);
void		*ft_routine_philosophers(void *arg);
int		philo_cleaner(t_table *table, int i);
void		kill(t_table *table, int i);

//Init_Functions
void		init_table(t_table *table);
void		init_philosophers(t_table *table, int num_philos);
void		set_forks(t_table *table);
void		start_threads(t_table *table);

//Philophers Actions
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);

//Control time
void		precise_usleep(long miliseconds);
long		current_timestamp(void);

#endif
