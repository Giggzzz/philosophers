/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:26:42 by gudias            #+#    #+#             */
/*   Updated: 2022/06/21 16:49:31 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	init_params(t_params *params, int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->meals_to_eat = ft_atoi(argv[5]);
	else
		params->meals_to_eat = -1;
	pthread_mutex_init(&(params->print_lock), NULL);
	params->start_time = get_current_time();
	params->sim_finished = 0;
	return (1);
}

pthread_mutex_t	**init_mutex_forks(int	nb_forks)
{
	pthread_mutex_t	**forks_mutex;
	int		i;

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

static void	init_philo(t_philo *philo, int id, pthread_mutex_t **forks_mutex, t_params *params){

		philo->id = id;
		philo->fork1 = forks_mutex[id - 1];
		if (id == params->nb_philos)
			philo->fork2 = forks_mutex[0];
		else
			philo->fork2 = forks_mutex[id];
		philo->last_meal = 0;
		philo->meal_count = 0;
		philo->params = params;
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

pthread_t	**create_threads(int nb, t_philo **philos)
{
	pthread_t	**threads;
	int		i;

	threads = malloc (sizeof (pthread_t *) * (nb + 1));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		threads[i] = malloc (sizeof (pthread_t));
		if (!threads[i])
		{
			free_threads(threads);
			return (NULL);
		}
		pthread_create(threads[i], NULL, &thread_philo_routine, philos[i]);
		usleep(1);
		i++;
	}
	threads[nb] = NULL;
	return (threads);
}	
