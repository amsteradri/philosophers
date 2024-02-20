/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:48:58 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/20 11:53:02 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	static struct timeval		unix_clock;
	struct timeval				current_time;

	if (unix_clock.tv_sec == 0 && unix_clock.tv_usec == 0)
	{
		if (gettimeofday(&unix_clock, NULL) == -1)
		{
			printf("Error getting time\n");
			return (0);
		}
	}
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error getting time\n");
		return (0);
	}
	return (((current_time.tv_sec - unix_clock.tv_sec) * 1000) + \
	((current_time.tv_usec - unix_clock.tv_usec) / 1000));
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

void	init_mutex(t_args *args)
{
	pthread_mutex_init(&args->lock_print, NULL);
	pthread_mutex_init(&args->lock_death, NULL);
	pthread_mutex_init(&args->lock_end_game, NULL);
	pthread_mutex_init(&args->lock_meals_stop, NULL);
	pthread_mutex_init(&args->lock_meals_eaten, NULL);
	pthread_mutex_init(&args->lock_last_meal_time, NULL);
}

void	init_philo_mutex(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	init_mutex(args);
	while (i < args->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal_time = get_time();
		philos[i].left_fork = &args->forks[i];
		philos[i].right_fork = &args->forks[(i + 1) % args->n_philos];
		philos[i].args = args;
		pthread_create(&philos[i].threads, NULL, routine, &philos[i]);
		pthread_create(&philos[i].death_check, NULL, check_death, &philos[i]);
		pthread_create(&philos[i].meals_check, NULL, check_meals, &philos[i]);
		i++;
	}
}

void	log_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->lock_end_game);
	if (philo->args->end_game)
	{
		pthread_mutex_unlock(&philo->args->lock_end_game);
		return ;
	}
	pthread_mutex_unlock(&philo->args->lock_end_game);
	pthread_mutex_lock(&philo->args->lock_print);
	printf("%lld philo[%d] %s", get_time(), philo->id, str);
	pthread_mutex_unlock(&philo->args->lock_print);
}
