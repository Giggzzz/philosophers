/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:26:42 by gudias            #+#    #+#             */
/*   Updated: 2022/06/25 03:25:18 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg("bad argument count"));
	while (*(++argv))
	{
		if (!is_number_pos(*argv))
			return (err_msg("invalid arguments"));
	}
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->meals_to_eat = ft_atoi(argv[5]);
	else
		params->meals_to_eat = -1;
	params->start_time = get_current_time();
	sem_unlink("/ended");
	sem_unlink("/print");
	sem_unlink("/forks");
	params->ended_sem = sem_open("/ended", O_CREAT, 0644, 1);
	params->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	params->forks_sem = sem_open("/forks", O_CREAT, 0644, params->nb_philos);
	return (0);
}

void	init_philo(t_philo *philo, int id, t_params *params)
{
	philo->id = id;
	philo->last_meal = 0;
	//sem_unlink("/lastmeal");
	philo->last_meal_sem = sem_open("/lastmeal", O_CREAT, 0644, 1);
	philo->meal_count = 0;
	philo->params = params;
}

t_philo	**create_philos(t_params *params)
{
	t_philo	**philos;
	int		i;

	philos = malloc (sizeof (t_philo *) * (params->nb_philos + 1));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < params->nb_philos)
	{
		philos[i] = malloc (sizeof (t_philo));
		if (!philos[i])
		{
			free_philos(philos);
			return (NULL);
		}
		init_philo(philos[i], i + 1, params);
		i++;
	}
	philos[params->nb_philos] = NULL;
	return (philos);
}
