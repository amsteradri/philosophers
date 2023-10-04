/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:31:43 by adgutier          #+#    #+#             */
/*   Updated: 2023/07/15 17:31:43 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
#include <limits.h>
# include <string.h>


typedef struct s_args
{
    int n_philos;
    int must_eat;
    int n_meals_eaten;

    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
   
    pthread_mutex_t		*forks;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		lock_death;
	pthread_mutex_t		lock_meals_stop;
	pthread_mutex_t		lock_meals_eaten;
	pthread_mutex_t		lock_last_meal_time;

	bool			end_game;
} t_args;

typedef struct s_philo
{
	int					id;
	long long			last_meal_time;
	pthread_t			*threads;
	pthread_t			death_check;
	pthread_t			meals_check;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_args				*args;
}	t_philo;

void	init_philos_and_mutexes(t_philo *philos, t_args *args);
void init_forks(t_args *args);

#endif