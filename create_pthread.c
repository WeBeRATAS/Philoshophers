/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:39:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 19:40:01 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void start_simulation(t_data *data) {
    for (int i = 0; i < data->num_philosophers; i++) {
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
    }

    for (int i = 0; i < data->num_philosophers; i++) {
        pthread_join(data->philosophers[i].thread, NULL);
    }
}
