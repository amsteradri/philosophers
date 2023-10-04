/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   froks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:48:58 by adgutier          #+#    #+#             */
/*   Updated: 2023/10/04 16:48:58 by adgutier         ###   ########.fr       */
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
			printf("Error getting time of day\n");
			return (0);
		}
	}
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error getting time of day\n");
		return (0);
	}
	return (((current_time.tv_sec - unix_clock.tv_sec) * 1000) + \
	((current_time.tv_usec - unix_clock.tv_usec) / 1000));
}

void init_forks(t_args *args)
{
    int i;

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
	if (philo->args->stop_sim)
		return ;
	pthread_mutex_lock(&philo->args->lock_print);
	printf("%lld %d %s", get_time(), philo->id, str);
	pthread_mutex_unlock(&philo->args->lock_print);
}

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->args->end_game)
	{
		if ((get_time() - philo->last_meal_time) >= philo->args->time_to_die)
		{
			pthread_join(philo->death_check, NULL);
			pthread_mutex_lock(&philo->args->lock_death);
			log_message(philo, "is dead\n");
			philo->args->end_game = true;
			pthread_mutex_unlock(&philo->args->lock_death);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

void	*check_meals(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->args->stop_sim)
	{
		if (philo->args->n_meals > 0 && (philo->args->n_meals_eaten >= \
		(philo->args->n_meals * philo->args->n_philos)))
		{
			pthread_join(philo->meals_check, NULL);
			pthread_mutex_lock(&philo->args->lock_meals_stop);
			philo->args->stop_sim = true;
			pthread_mutex_unlock(&philo->args->lock_meals_stop);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_create(&philo->death_check, NULL, check_death, philo);
	pthread_create(&philo->meals_check, NULL, check_meals, philo);
	while (!philo->args->end_game)
	{
		if (philo->args->n_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			log_message(philo, "has taken a fork\n");
			return (NULL);
		}
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}