/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:11:59 by gudias            #+#    #+#             */
/*   Updated: 2022/07/05 18:13:34 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_philo_dead(t_philo *philo)
{
	long int	timestamp;

	timestamp = get_current_time() - philo->params->start_time;
	if (philo->last_meal + philo->params->time_to_die < timestamp)
		return (1);
	return (0);
}

/*static int	check_all_ate(t_philo **philos)
{
	int	i;

	if ((*philos)->params->meals_to_eat <= 0)
		return (0);
	i = 0;
	while (philos[i])
	{
		if (philos[i]->meal_count < philos[i]->params->meals_to_eat)
			return (0);
		i++;
	}
	kill_all_process(philos);
	return (1);
}*/

void	*thread_check_death(void *arg)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *) arg;
	while (1)
	{
		time = get_current_time();
		if (is_philo_dead(philo))
		{
			sem_wait(philo->params->print_sem);
			time = time - philo->params->start_time;
			printf("%ld\t%d %s\n", time, philo->id, MSG_DIE);
			sem_post(philo->params->ended_sem);
			return (NULL);
		}
		while (get_current_time() == time)
			usleep(100);
	}
	return (NULL);
}

void	*thread_wait_end(void *arg)
{
	t_philo	**philos;

	philos = (t_philo **) arg;
	sem_wait(philos[0]->params->ended_sem);
	philos[0]->params->ended = 1;
	sem_post(philos[0]->params->is_full_sem);
	kill_all_process(philos);
	return (NULL);
}

void	*thread_wait_all_full(void *arg)
{
	t_params	*params;
	int			is_full;

	params = (t_params *) arg;
	is_full = 0;
	while (is_full != params->nb_philos)
	{	
		sem_wait(params->is_full_sem);
		if (params->ended)
			return (NULL);
		is_full++;
	}
	sem_post(params->ended_sem);
	return (NULL);
}
