/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/08 19:36:07 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	*thread_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	printf("[%d] %d arrives and start to wait\n", get_current_time(), philo->id);
	usleep(2000);

	printf("[%d] %d wait for fork\n", get_current_time(), philo->id);
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);
	
	printf("[%d] %d start eating\n", get_current_time(), philo->id);	
	//printf("%d ttd\n", philo->params->time_to_die);	
	//printf("%d tte\n", philo->params->time_to_eat);	
	//printf("%d tts\n", philo->params->time_to_sleep);	
	usleep(10000);
	printf("[%d] %d finished eating\n", get_current_time(), philo->id);	
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (NULL);
}

static pthread_t	*start_thread_philo(int id, t_params *params, pthread_mutex_t **forks_mutex)
{
	pthread_t	*t;
	t_philo		*philo;

	t = malloc (sizeof (pthread_t));
	if (!t)
		return (NULL);

	philo = malloc (sizeof (t_philo));
	if (!philo)
		return (NULL);

	philo->fork1 = forks_mutex[id];
	if (id == 3) //id == params->nb_philos-1
		philo->fork2 = forks_mutex[0];
	else
		philo->fork2 = forks_mutex[id  + 1];
	philo->id = id;
	philo->params = params;

	pthread_create(t, NULL, &thread_func, philo);
	return (t);
	//pthread_join(t, NULL);
}

int	main (int argc, char **argv)
{
	t_params	params;

	(void) argc;
	(void) argv;
	/*
	if (!check_args(argc, argv))
		return (1);

	init_params(&params, argv);
	*/
	//init_forks(atoi(argv[1])); //init_mutex
	//init_philos(argv); //init_threads

	//INIT MUTEX (forks)
	pthread_mutex_t **forks_mutex;
	forks_mutex = malloc (sizeof (pthread_mutex_t *) * 4);
	if (!forks_mutex)
		return (printf("MALLOC ERROR\n"));
	int	i = 0;
	//pthread_mutex_t *fork;
	while (i < 4)
	{
		forks_mutex[i] = malloc (sizeof (pthread_mutex_t));
		if (!forks_mutex[i])
			return (printf("MALLOC ERROR\n"));
		pthread_mutex_init(forks_mutex[i], NULL);

		//forks_mutex[i] = fork;
		i++;
	}
	/*
	pthread_mutex_t	*fork0 = malloc (sizeof (pthread_mutex_t));
	if (!fork0)
		return (printf("MALLOC ERROR\n"));
	*fork0 = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(fork0, NULL);
	
	forks_mutex[0] = fork0;
	*/
	//pthread_mutex_t	fork1 = PTHREAD_MUTEX_INITIALIZER;
	//pthread_mutex_t	fork2 = PTHREAD_MUTEX_INITIALIZER;
	//pthread_mutex_t	fork3 = PTHREAD_MUTEX_INITIALIZER;
	

	//THREADS
	pthread_t **philos_thread;
	philos_thread = malloc (sizeof (pthread_t *) * 4);
	if (!philos_thread)
		return (printf("MALLOC ERROR\n"));
	//pthread_t	t1;
	i = -1;
	while (++i < 4)
		philos_thread[i] = start_thread_philo(i, &params, forks_mutex);
	//pthread_t	t2;
	//pthread_t	t3;
	//pthread_t	t4;
	
	//INIT T_PHILO(id, fork1, fork2)
	//t_philo		philo1;
	//t_philo		philo2;
	//t_philo		philo3;
	//t_philo		philo4;

	//philo1.fork1 = forks_mutex[0];
	//philo1.id = 1;
	//philo1.params = &params;
	//philo1.fork2 = forks_mutex[1];
//	philo2.fork1 = forks_mutex[1];
//	philo2.id = 2;
//	philo2.params = &params;
//	philo2.fork2 = forks_mutex[2];
//	philo3.fork1 = forks_mutex[2];
//	philo3.id = 3;
//	philo3.params = &params;
//	philo3.fork2 = forks_mutex[3];
//	philo4.fork1 = forks_mutex[3];
//	philo4.id = 4;
//	philo4.params = &params;
//	philo4.fork2 = forks_mutex[0];

	//pthread_create(&t1, NULL, &thread_func, &philo1);
//	pthread_create(&t2, NULL, &thread_func, &philo2);
//	pthread_create(&t3, NULL, &thread_func, &philo3);
//	pthread_create(&t4, NULL, &thread_func, &philo4);
	
	//wait
	i = -1;
	while (++i < 4)
		pthread_join(*(philos_thread[i]), NULL);
	//pthread_join(t1, NULL);
//	pthread_join(t2, NULL);
//	pthread_join(t3, NULL);
//	pthread_join(t4, NULL);
	//printf("end: %d\n", arg);
	return (0);
}

