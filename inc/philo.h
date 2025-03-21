/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/21 11:00:31 by rbuitrag         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	t_philo			**philos;
	int				num_philos;
	long			tto_die;
	long			tto_eat;
	long			tto_sleep;
	int				each_eat;
	int				total_full;
	pthread_mutex_t	stop_m;
	bool			stop;
	long			reset_time;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
 	bool			full;
	t_table			*table;
	pthread_t		philo_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	last_m;
	long			last_meal;
}	t_philo;

/*Main_Functions **/ 
bool		check_args(int ac, char **av, t_table *table);
void		*ft_routine_philosophers(void *arg);
void		philo_controller(t_table *table);
void		kill(t_table *table, int i, long time_now);
bool		simulation(t_table *table);

/*Init_Functions * */
void		init_table(t_table *table);
void		init_philosophers(t_table *table, int num_philos);
void		set_forks(t_table *table);
void		start_threads(t_table *table);

/*Philophers Actions * */
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);

/* Forks - Tenedores utiles*/
bool		take_fork(pthread_mutex_t *fork, t_philo *philo);
void		drop_forks(t_philo *philo);
bool		handle_forking(t_philo *philo, pthread_mutex_t *first, \
			pthread_mutex_t *second);

/*Control time **/
void		precise_usleep(long miliseconds);
long		get_time_ml(void);

#endif
