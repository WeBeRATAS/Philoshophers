/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:40:52 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 19:40:55 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void *philosopher_routine(void *arg) {
    t_philosopher *philosopher = (t_philosopher *)arg;

    while (1) {
        // Pensar
        printf("Filósofo %d está pensando.\n", philosopher->id);
        usleep(1000);

        // Tomar los tenedores
        pthread_mutex_lock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->right_fork);

        // Comer
        printf("Filósofo %d está comiendo.\n", philosopher->id);
        usleep(1000);

        // Soltar los tenedores
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);

        // Dormir
        printf("Filósofo %d está durmiendo.\n", philosopher->id);
        usleep(1000);
    }
    return NULL;
}
