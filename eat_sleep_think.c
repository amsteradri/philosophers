/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:52:51 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/21 13:11:23 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void forks(t_philo *philo)
{
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        log_message(philo, "has taken a fork\n");
        if (pthread_mutex_trylock(philo->left_fork) != 0)
        {
            pthread_mutex_unlock(philo->right_fork);
            return;
        }
        log_message(philo, "has taken a fork\n");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        log_message(philo, "has taken a fork\n");
        if (pthread_mutex_trylock(philo->right_fork) != 0)
        {
            pthread_mutex_unlock(philo->left_fork);
            return;
        }
        log_message(philo, "has taken a fork\n");
    }
}


void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->lock_last_meal_time);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->args->lock_last_meal_time);

    log_message(philo, "is eating\n");
    usleep(philo->args->time_to_eat * 1000);

    pthread_mutex_lock(&philo->args->lock_meals_eaten);
    philo->args->n_meals_eaten++;
    pthread_mutex_unlock(&philo->args->lock_meals_eaten);

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	log_message(philo, "is sleeping\n");
	usleep(philo->args->time_to_sleep * 1000);
	log_message(philo, "is thinking\n");
}