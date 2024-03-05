/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:54:40 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/20 11:10:36 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end_game(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->lock_end_game);
	if (philo->args->end_game)
	{
		pthread_mutex_unlock(&philo->args->lock_end_game);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->lock_end_game);
	return (0);
}

int	check_time_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->lock_last_meal_time);
	if ((get_time() - philo->last_meal_time) > philo->args->time_to_die)
	{
		pthread_mutex_unlock(&philo->args->lock_last_meal_time);
		pthread_mutex_lock(&philo->args->lock_death);
		log_message(philo, "is dead\n");
		pthread_mutex_lock(&philo->args->lock_end_game);
		philo->args->end_game = true;
		pthread_mutex_unlock(&philo->args->lock_death);
		pthread_mutex_unlock(&philo->args->lock_end_game);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->lock_last_meal_time);
	return (0);
}

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (check_end_game(philo))
			return (NULL);
		if (check_time_to_die(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
