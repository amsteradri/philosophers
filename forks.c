/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:48:58 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/26 14:09:51 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	tempo(t_philo *philo, size_t t_slp)
{
	size_t	t;

	t = get_time();
	while (philo->args->end_game == 0)
	{
		if (get_time() - t > t_slp)
			break ;
		usleep(100);
	}
}

void	init_forks(t_args *args)
{
	int	i;

	i = 0;
	args->forks = malloc(sizeof(t_args) * args->n_philos);
	while (i < args->n_philos)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
}

void	init_philos_and_mutexes(t_philo *philos, t_args *args)
{
	int	i;

	pthread_mutex_init(&args->lock_print, NULL);
	pthread_mutex_init(&args->lock_death, NULL);
	pthread_mutex_init(&args->lock_meals_stop, NULL);
	pthread_mutex_init(&args->lock_meals_eaten, NULL);
	pthread_mutex_init(&args->lock_last_meal_time, NULL);
	philos->threads = malloc(sizeof(pthread_t) * args->n_philos);
	i = 0;
	while (i < args->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal_time = get_time();
		philos[i].left_fork = &args->forks[i];
		philos[i].right_fork = &args->forks[(i + 1) % args->n_philos];
		philos[i].args = args;
		pthread_create(&philos->threads[i], NULL, routine, &philos[i]);
		i++;
	}
}

void	log_message(t_philo *philo, char *str)
{
	if (philo->args->end_game)
		return ;
	pthread_mutex_lock(&philo->args->lock_print);
	printf("%zu philo[%d] %s", get_time(), philo->id, str);
	pthread_mutex_unlock(&philo->args->lock_print);
}
