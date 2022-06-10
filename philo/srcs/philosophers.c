/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/10 18:30:27 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	g_start;

int	main (int argc, char **argv)
{
	t_params	params;
	pthread_mutex_t	**forks_mutex;
	t_philo		**philos;
	pthread_t	**threads;

	if (!check_args(argc, argv))
		return (1);

	init_params(&params, argv);
	struct timeval starttime;
	gettimeofday(&starttime, NULL);
	g_start = starttime.tv_usec;
	forks_mutex = init_mutex_forks(params.nb_philos);
	philos = init_philos(&params, forks_mutex);
	threads = init_threads(params.nb_philos, philos);

	wait_all_threads(params.nb_philos, threads);

	// free/destroy forks_mutex, philos, threads
	free_all(forks_mutex, threads, philos);
	return (0);
}
