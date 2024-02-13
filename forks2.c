/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:00:51 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/13 11:41:34 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->args->lock_end_game);
		if (philo->args->end_game)
		{
			pthread_mutex_unlock(&philo->args->lock_end_game);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->lock_end_game);
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
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->lock_last_meal_time);
		usleep(1000);
	}
	return (NULL);
}

void	*check_meals(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->args->lock_end_game);
		if (philo->args->end_game)
		{
			pthread_mutex_unlock(&philo->args->lock_end_game);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->lock_end_game);
		pthread_mutex_lock(&philo->args->lock_meals_eaten);
		if (philo->args->n_meals > 0 && (philo->args->n_meals_eaten >= \
		(philo->args->n_meals * philo->args->n_philos)))
		{
			pthread_mutex_unlock(&philo->args->lock_meals_eaten);
			pthread_mutex_lock(&philo->args->lock_meals_stop);
			pthread_mutex_lock(&philo->args->lock_end_game);
			philo->args->end_game = true;
			pthread_mutex_unlock(&philo->args->lock_meals_stop);
			pthread_mutex_unlock(&philo->args->lock_end_game);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->lock_meals_eaten);
		usleep(1000);
	}
	return (NULL);
}

void wait_threads(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->args->n_philos)
	{
		pthread_join(philos[i].threads, NULL);
		pthread_join(philos[i].death_check, NULL);
		pthread_join(philos[i].meals_check, NULL);
		i++;
	}
}


void	free_destroy_end(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < philos->args->n_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->lock_last_meal_time);
	pthread_mutex_destroy(&args->lock_print);
	pthread_mutex_destroy(&args->lock_meals_stop);
	pthread_mutex_destroy(&args->lock_death);
	pthread_mutex_destroy(&args->lock_end_game);
	pthread_mutex_destroy(&args->lock_meals_eaten);
	free(philos);
	free(args->forks);
}
