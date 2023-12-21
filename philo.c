/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:31:28 by adgutier          #+#    #+#             */
/*   Updated: 2023/12/21 12:58:17 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					p;
	int					n;
	unsigned int		res;

	p = 0;
	n = 1;
	res = 0;
	while ((str[p] >= 9 && str[p] <= 13) || (str[p] == 32))
		p++;
	if (str[p] == '+' || str[p] == '-')
	{
		if (str[p] == '-')
			n = n * -1;
		p++;
	}
	while (str[p] >= '0' && str[p] <= '9')
	{
		res = (str[p] - '0') + (res * 10);
		p++;
	}
	if (res > 2147483648 && n == -1)
		return (0);
	if (res > 2147483647 && n == 1)
		return (-1);
	return (res * n);
}

void init_struct(t_args *args)
{
	args->n_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->n_meals = 0;
	args->n_meals_eaten = 0;
}

void parse_args(int argc, char **argv, t_args *args)
{

	args->n_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->end_game = false;
	if(argc == 6)
	{
		args->n_meals = ft_atoi(argv[5]);
		if (args->n_meals <= 0)
		{
			printf("Invalid arguments\n");
			exit(0);
		}
	}
	if (argc < 5 || args->n_philos <= 0 || args->time_to_die <= 0 \
		|| args->time_to_sleep <= 0 || args->time_to_eat <= 0)
	{
		printf("Invalid arguments\n");
		exit(0);
	}
}


// while true; do ./philo 5 800 200 200 7 | grep eating | wc -l;  done
int main(int argc, char **argv)
{
	t_args args;
	t_philo *philos;

	if(argc < 5)
	{
		printf("Error: incomplete arguments");
		exit(0);
	}
	init_struct(&args);
	//printf("ARGSSSSS%d\n", argc);
    parse_args(argc, argv, &args);
	philos = malloc(sizeof(t_philo) * args.n_philos);
	if (!philos)
		return (0);
	init_forks(&args);
	init_philos_and_mutexes(philos, &args);
	wait_threads(philos);
	free_destroy_end(philos, &args);
	return(0);
}
