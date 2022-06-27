/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:11:59 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 18:30:17 by gudias           ###   ########.fr       */
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
			printf("%ld\t%d %s\n", time - philo->params->start_time, philo->id, MSG_DIE);
			sem_post(philo->params->ended_sem);
			return (NULL);
		}
		//if (check_all_ate(philos))
		//	return (NULL);
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
	kill_all_process(philos);
	return (NULL);
}
