/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/24 19:41:57 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_params		params;
	pthread_mutex_t	**forks_mutex;
	t_philo			**philos;
	pthread_t		**threads;
	pthread_t		thread_checker;

	if (init_params(&params, argc, argv))
		return (1);
	forks_mutex = init_mutex_forks(params.nb_philos);
	if (!forks_mutex)
		return (err_msg("couldn't init mutex"));
	philos = create_philos(&params, forks_mutex);
	if (!philos)
		return (err_msg("couldn't init philosophers"));
	threads = create_threads(params.nb_philos, philos, &thread_checker);
	if (!threads)
		return (err_msg("couldn't create threads"));
	wait_all_threads(threads, &thread_checker);
	free_all(forks_mutex, threads, philos);
	pthread_mutex_destroy(&(params.print_lock));
	pthread_mutex_destroy(&(params.ended_lock));
	return (0);
}
