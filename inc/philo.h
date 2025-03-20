/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/03/20 21:16:49 by rbuitrag         ###   ########.fr       */
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
	pthread_t		control_thread;
	int				num_philos;
	long long			tto_die;
	long long			tto_eat;
	long long			tto_sleep;
	int				each_eat;
	pthread_mutex_t	stop_m;
	bool			stop;
	long long			reset_time;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				is_full;
	t_table			*table;
	pthread_t		philo_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	last_m;
	long long			last_meal;
}	t_philo;

/*Main_Functions **/ 
bool		check_args(int ac, char **av, t_table *table);
void		*ft_routine_philosophers(void *arg);
void		*philo_controller(void *arg);
void		kill(t_table *table, int i, long long now);

/*Init_Functions * */
void		init_table(t_table *table);
void		init_philosophers(t_table *table, int num_philos);
void		set_forks(t_table *table);
void		start_threads(t_table *table);

/*Philophers Actions * */
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);

/*Control time **/
void		precise_usleep(long long miliseconds);
long		get_time_ml(void);

#endif
