/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:46:06 by gudias            #+#    #+#             */
/*   Updated: 2022/06/24 03:19:40 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	simulation_ended(t_params *params)
{
	int	end;

	pthread_mutex_lock(&(params->ended_lock));
	end = params->ended;
	pthread_mutex_unlock(&(params->ended_lock));
	return (end);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	if (simulation_ended(philo->params))
	{
		pthread_mutex_unlock(philo->fork1);
		return (0);
	}
	print_msg(MSG_FORK, philo->params, philo->id);
	if (philo->fork1 == philo->fork2)
	{
		tweaked_usleep(philo->params->time_to_die);
		return (0);
	}
	pthread_mutex_lock(philo->fork2);
	if (simulation_ended(philo->params))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (0);
	}
	print_msg(MSG_FORK, philo->params, philo->id);
	return (1);
}

static int	take_lunch(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_meal_lock));
	philo->last_meal = get_current_time() - philo->params->start_time;
	pthread_mutex_unlock(&(philo->last_meal_lock));
	if (simulation_ended(philo->params))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (0);
	}
	print_msg(MSG_EAT, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	philo->meal_count++;
	if (simulation_ended(philo->params))
		return (0);
	return (1);
}

static int	have_a_good_night(t_philo *philo)
{
	if (simulation_ended(philo->params))
		return (0);
	print_msg(MSG_SLEEP, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_sleep);
	if (simulation_ended(philo->params))
		return (0);
	return (1);
}

void	*thread_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		tweaked_usleep(philo->params->time_to_eat);
	while (!simulation_ended(philo->params))
	{
		if (!take_forks(philo))
			break ;
		if (!take_lunch(philo))
			break ;
		if (!have_a_good_night(philo))
			break ;
		print_msg(MSG_THINK, philo->params, philo->id);
	}
	return (NULL);
}
