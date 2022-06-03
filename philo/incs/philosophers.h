/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:01:46 by gudias            #+#    #+#             */
/*   Updated: 2022/06/03 17:39:52 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef	struct s_philo
{
	int	id;
	int	ttd;
	int	tte;
	int	tts;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philo;

#endif
