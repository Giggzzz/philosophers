/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:46:06 by gudias            #+#    #+#             */
/*   Updated: 2022/06/25 03:48:10 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->params->forks_sem);

	print_msg(MSG_FORK, philo->params, philo->id);
	if (philo->params->nb_philos == 1)
	{
	//	tweaked_usleep(philo->params->time_to_die);
		return (0);
	}

	sem_wait(philo->params->forks_sem);
	
	print_msg(MSG_FORK, philo->params, philo->id);
	return (1);
}

static int	take_lunch(t_philo *philo)
{
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_current_time() - philo->params->start_time;
	sem_post(philo->last_meal_sem);
	
	printf("%d lastmeal: %ld\n", philo->id, philo->last_meal);
	print_msg(MSG_EAT, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_eat);
	sem_post(philo->params->forks_sem);	
	sem_post(philo->params->forks_sem);	
	philo->meal_count++;
	return (1);
}

static int	have_a_good_night(t_philo *philo)
{
	print_msg(MSG_SLEEP, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_sleep);
	return (1);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		if (!take_forks(philo))
			break ;
		if (!take_lunch(philo))
			break ;
		if (!have_a_good_night(philo))
			break ;
		print_msg(MSG_THINK, philo->params, philo->id);
	}
}
