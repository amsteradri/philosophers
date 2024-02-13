/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:31:43 by adgutier          #+#    #+#             */
/*   Updated: 2024/02/13 11:38:10 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				n_philos;
	int				n_meals;
	int				n_meals_eaten;

	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;

	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_meals_stop;
	pthread_mutex_t	lock_meals_eaten;
	pthread_mutex_t	lock_end_game;
	pthread_mutex_t	lock_last_meal_time;

	bool			end_game;
}					t_args;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	
	pthread_t		threads;
	pthread_t		death_check;
	pthread_t		meals_check;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
}					t_philo;

int					ft_atoi(const char *str);
void				init_struct(t_args *args);
void				parse_args(int argc, char **argv, t_args *args);
void				init_philos_and_mutexes(t_philo *philos, t_args *args);
void				init_forks(t_args *args);
long long			get_time(void);
void				tempo(t_philo *philo, size_t t_slp);
void				log_message(t_philo *philo, char *str);
void				*check_death(void *args);
void				*check_meals(void *args);
void				*routine(void *args);
void				forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_think(t_philo *philo);
void				wait_threads(t_philo *philos);
void				free_destroy_end(t_philo *philos, t_args *args);
#endif