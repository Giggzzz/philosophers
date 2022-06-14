/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/14 17:45:22 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main (int argc, char **argv)
{
	t_params	params;
	pthread_mutex_t	**forks_mutex;
	t_philo		**philos;
	pthread_t	**threads;

	if (!check_args(argc, argv))
		return (1);

	init_params(&params, argv);
	forks_mutex = init_mutex_forks(params.nb_philos);
	philos = init_philos(&params, forks_mutex);
	threads = init_threads(params.nb_philos, philos);

	wait_all_threads(params.nb_philos, threads);

	free_all(forks_mutex, threads, philos);
	pthread_mutex_destroy(&(params.print_lock));
	return (0);
}
