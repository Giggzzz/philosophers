/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:54:03 by gudias            #+#    #+#             */
/*   Updated: 2022/06/28 15:54:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc (sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
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

char	*ft_itoa(int n)
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
