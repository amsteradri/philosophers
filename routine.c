/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:08:57 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/13 11:11:41 by adgutier         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->args->lock_end_game);
		if (philo->args->end_game)
		{
			pthread_mutex_unlock(&philo->args->lock_end_game);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->lock_end_game);
		if (philo->args->n_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			log_message(philo, "has taken a fork\n");
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		forks(philo);
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}
