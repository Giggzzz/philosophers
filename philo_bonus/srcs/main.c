/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 18:06:39 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_params		params;
	t_philo			**philos;
	pthread_t		end_waiter;

	if (init_params(&params, argc, argv))
		return (1);
	philos = create_philos(&params);
	if (!philos)
		return (err_msg("couldn't init philosophers"));
	if (create_process(philos))
		return (err_msg("couldn't create process"));
	pthread_create(&end_waiter, NULL, &thread_wait_end, philos);
	pthread_join(end_waiter, NULL);
	//wait_all_process(philos);
	free_all(philos);
	sem_close(params.ended_sem);
	sem_close(params.print_sem);
	sem_close(params.forks_sem);
	return (0);
}
