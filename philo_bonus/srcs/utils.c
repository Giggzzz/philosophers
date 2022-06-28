/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:16:32 by gudias            #+#    #+#             */
/*   Updated: 2022/06/28 15:54:40 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(char *msg, t_params *params, int id)
{
	long int	timestamp;

	timestamp = get_current_time() - params->start_time;
	sem_wait(params->print_sem);
	printf("%ld\t%d %s\n", timestamp, id, msg);
	sem_post(params->print_sem);
}

long int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

void	tweaked_usleep(int ms_time)
{
	long int	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms_time)
		usleep(100);
}

int	is_number_pos(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' && *(str + 1))
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	num;

	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		if (num > 2147483647)
			return (0);
		i++;
	}
	return (num);
}
