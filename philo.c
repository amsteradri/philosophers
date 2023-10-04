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

void init_struct(t_philo *philo)
{
	philo->number_of_philosophers = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->must_eat = 0;
}
void parse_args(int argc, char **argv, t_philo *philo)
{
	if(argc == 5)
	{
		philo->number_of_philosophers = ft_atoi(argv[1]);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
	}
	else if(argc == 6)
	{
		philo->number_of_philosophers = ft_atoi(argv[1]);
		philo->time_to_die = ft_atoi(argv[2]);
		philo->time_to_eat = ft_atoi(argv[3]);
		philo->time_to_sleep = ft_atoi(argv[4]);
		philo->must_eat = ft_atoi(argv[5]);
	}
}

int main(int argc, char **argv)
{
	t_philo philo;

	// if(argc < 4)
	// {
	// 	perror("Philo: missing argument");
	// 	exit(0);
	// }
	init_struct(&philo);
	printf("ARGSSSSS%d\n", argc);
    parse_args(argc, argv, &philo);
	printf("fILOSOFOS:%d\n", philo.number_of_philosophers);
	printf("T_MUERTE:%d\n", philo.time_to_die);
	printf("T_COMER:%d\n", philo.time_to_eat);
	printf("T_DORMIR:%d\n", philo.time_to_sleep);
	printf("T_DEBE_COMER:%d\n", philo.must_eat);

}
