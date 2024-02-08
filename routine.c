/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:08:57 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/08 10:00:06 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	actions(t_philo *philo)
{
	forks(philo);
	eat(philo);
	sleep_think(philo);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_create(&philo->death_check, NULL, check_death, philo);
	if (philo->args->n_meals > 0)
	{
		pthread_create(&philo->meals_check, NULL, check_meals, philo);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->args->end_game)
	{
		if (philo->args->n_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			log_message(philo, "has taken a fork\n");
			return (NULL);
		}
		actions(philo);
	}
	pthread_join(philo->death_check, NULL);
	if (philo->args->n_meals > 0)
	{
		pthread_join(philo->meals_check, NULL);
	}
	return (NULL);
}
