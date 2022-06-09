/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:26:42 by gudias            #+#    #+#             */
/*   Updated: 2022/06/04 04:53:38 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_number_pos(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' && *(str + 1))
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Bad argument count\n");
		return (0);
	}
	while (*(++argv))
	{
		if (!is_number_pos(*argv))
		{
			printf("invalid arguments\n");
			return (0);
		}
	}
	return (1);
}

void	init_params(t_params *params, char **argv)
{
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_sleep = ft_atoi(argv[3]);
	params->time_to_eat = ft_atoi(argv[4]);
	if (argv[5])
		params->min_turns = ft_atoi(argv[5]);
	else
		params->min_turns = -1;
}

/*
void	init_forks(int nb_forks)
{
}

void	init_philos(int argc, char **argv)
{

}
*/
