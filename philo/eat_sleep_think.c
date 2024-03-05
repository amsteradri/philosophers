/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:52:51 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/20 10:09:25 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		log_message(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		log_message(philo, "has taken a fork\n");
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		log_message(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		log_message(philo, "has taken a fork\n");
	}
}

void	eat(t_philo *philo)
{
	long long int	pass_toeat;

	pthread_mutex_lock(&philo->args->lock_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->args->lock_last_meal_time);
	log_message(philo, "is eating\n");
	pass_toeat = get_time() + philo->args->time_to_eat;
	while (get_time() < pass_toeat)
		usleep(200);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->args->lock_meals_eaten);
	philo->args->n_meals_eaten++;
	pthread_mutex_unlock(&philo->args->lock_meals_eaten);
}

void	sleep_think(t_philo *philo)
{
	long long int	pass_tosleep;

	pass_tosleep = get_time() + philo->args->time_to_sleep;
	log_message(philo, "is sleeping\n");
	while (get_time() < pass_tosleep)
		usleep(200);
	log_message(philo, "is thinking\n");
}
