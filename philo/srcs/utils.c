/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:16:32 by gudias            #+#    #+#             */
/*   Updated: 2022/06/16 18:05:56 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	err_msg(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

long int	get_current_time()
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

void	hacked_usleep(int ms_time)
{
	int	us_time;

	us_time = ms_time * 1000;
	while (us_time > 0)
	{
		usleep(100);
		us_time = us_time - 100;
	}
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
