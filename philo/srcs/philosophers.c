/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/21 16:49:51 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main (int argc, char **argv)
{
	t_params	params;
	pthread_mutex_t	**forks_mutex;
	t_philo		**philos;
	pthread_t	**threads;
	pthread_t	thread_checker;

	if (!init_params(&params, argc, argv))
		return (1);
	forks_mutex = init_mutex_forks(params.nb_philos);
	philos = create_philos(&params, forks_mutex);
	threads = create_threads(params.nb_philos, philos);
	pthread_create(&thread_checker, NULL, &thread_check_death, philos);
	//pthread_join(thread_checker, NULL);	
	wait_all_threads(params.nb_philos, threads);

	free_all(forks_mutex, threads, philos);
	pthread_mutex_destroy(&(params.print_lock));
	return (0);
}
