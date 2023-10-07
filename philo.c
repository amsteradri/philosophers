/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:31:28 by adgutier          #+#    #+#             */
/*   Updated: 2023/07/15 17:31:28 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (true);
	}
	return (false);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sig;
	long long	num;

	i = 0;
	sig = 1;
	num = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num * sig > INT_MAX)
			return (-1);
		if (num * sig < INT_MIN)
			return (0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sig);
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

int main(int argc, char **argv)
{
	t_args args;
	t_philo *philos;

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
	// printf("fILOSOFOS:%d\n", args.n_philos);
	// printf("T_MUERTE:%lld\n", args.time_to_die);
	// printf("T_COMER:%lld\n", args.time_to_eat);
	// printf("T_DORMIR:%lld\n", args.time_to_sleep);
	// printf("T_DEBE_COMER:%d\n", args.n_meals);

}
