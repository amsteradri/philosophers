/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:00:51 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/26 14:08:50 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->args->end_game)
	{
		if ((get_time()
				- philo->last_meal_time)
			>= (unsigned long long)philo->args->time_to_die)
		{
			pthread_join(philo->death_check, NULL);
			pthread_mutex_lock(&philo->args->lock_death);
			log_message(philo, "is dead\n");
			philo->args->end_game = true;
			pthread_mutex_unlock(&philo->args->lock_death);
			return (NULL);
		}
		usleep(300);
	}
	return (NULL);
}

void	*check_meals(void *args)
{
	t_philo	*philo;
	int		total_meals;

	philo = (t_philo *)args;
	while (!philo->args->end_game)
	{
		pthread_mutex_lock(&philo->args->lock_meals_eaten);
		total_meals = philo->args->n_meals_eaten;
		pthread_mutex_unlock(&philo->args->lock_meals_eaten);
		if (philo->args->n_meals > 0 && total_meals >= (philo->args->n_meals
				* philo->args->n_philos))
		{
			pthread_mutex_lock(&philo->args->lock_meals_stop);
			philo->args->end_game = true;
			pthread_mutex_unlock(&philo->args->lock_meals_stop);
		}
		usleep(300);
	}
	return (NULL);
}

void	wait_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->args->n_philos)
	{
		pthread_join(philos->threads[i], NULL);
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
	pthread_mutex_destroy(&args->lock_meals_eaten);
	free(philos->threads);
	free(philos);
	free(args->forks);
}
