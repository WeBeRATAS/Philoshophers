/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:41:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 19:41:16 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void init_data(t_data *data, int num_philosophers) {
    data->num_philosophers = num_philosophers;
    data->philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
    data->forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);

    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&data->forks[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++) {
        data->philosophers[i].id = i;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % num_philosophers];
    }
}
