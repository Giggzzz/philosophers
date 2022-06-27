/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:26:42 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 18:46:14 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define SEMNAME "/lastmeal"

#include "philosophers.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg("bad argument count"));
	while (*(++argv))
	{
		if (!is_number_pos(*argv))
			return (err_msg("invalid arguments"));
	}
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->meals_to_eat = ft_atoi(argv[5]);
	else
		params->meals_to_eat = -1;
	params->start_time = get_current_time();
	sem_unlink("/ended");
	sem_unlink("/print");
	sem_unlink("/forks");
	params->ended_sem = sem_open("/ended", O_CREAT, 0644, 0);
	params->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	params->forks_sem = sem_open("/forks", O_CREAT, 0644, params->nb_philos);
	return (0);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		s1_len = 0;
	int		s2_len = 0;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	while (s1[++i])
		s1_len++;
	i = -1;
	while (s2[++i])
		s2_len++;
	res = malloc (sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		res[i] = s2[i - s1_len];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	nb;

	len = ft_intlen(n);
	res = malloc (sizeof (char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (n < 0)
		res[0] = '-';
	else if (n == 0)
		res[0] = '0';
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (nb > 0)
	{
		res[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (res);
}

static void	init_philo(t_philo *philo, int id, t_params *params)
{
	char *name;

	philo->id = id;
	philo->last_meal = 0;

	name = ft_strjoin("/lastmeal", ft_itoa(philo->id));
	sem_unlink(name);
	philo->last_meal_sem = sem_open(name, O_CREAT, 0644, 1);
	philo->meal_count = 0;
	philo->params = params;
}

t_philo	**create_philos(t_params *params)
{
	t_philo	**philos;
	int		i;

	philos = malloc (sizeof (t_philo *) * (params->nb_philos + 1));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < params->nb_philos)
	{
		philos[i] = malloc (sizeof (t_philo));
		if (!philos[i])
		{
			free_philos(philos);
			return (NULL);
		}
		init_philo(philos[i], i + 1, params);
		i++;
	}
	philos[params->nb_philos] = NULL;
	return (philos);
}
