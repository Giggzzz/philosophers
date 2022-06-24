/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:26:42 by gudias            #+#    #+#             */
/*   Updated: 2022/06/24 19:00:44 by gudias           ###   ########.fr       */
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
	params->ended = 0;
	pthread_mutex_init(&(params->ended_lock), NULL);
	pthread_mutex_init(&(params->print_lock), NULL);
	return (0);
}

pthread_mutex_t	**init_mutex_forks(int nb_forks)
{
	pthread_mutex_t	**forks_mutex;
	int				i;

	forks_mutex = malloc (sizeof (pthread_mutex_t *) * (nb_forks + 1));
	if (!forks_mutex)
		return (NULL);
	i = 0;
	while (i < nb_forks)
	{
		forks_mutex[i] = malloc (sizeof (pthread_mutex_t));
		if (!forks_mutex[i])
		{
			free_forks_mutex(forks_mutex);
			return (NULL);
		}	
		pthread_mutex_init(forks_mutex[i], NULL);
		i++;
	}
	forks_mutex[nb_forks] = NULL;
	return (forks_mutex);
}

void	init_philo(t_philo *ph, int i, pthread_mutex_t **frks, t_params *params)
{
	ph->id = i;
	ph->fork1 = frks[i - 1];
	if (i == params->nb_philos)
		ph->fork2 = frks[0];
	else
		ph->fork2 = frks[i];
	ph->last_meal = 0;
	pthread_mutex_init(&(ph->last_meal_lock), NULL);
	ph->meal_count = 0;
	ph->params = params;
}

t_philo	**create_philos(t_params *params, pthread_mutex_t **forks_mutex)
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
		init_philo(philos[i], i + 1, forks_mutex, params);
		i++;
	}
	philos[params->nb_philos] = NULL;
	return (philos);
}
