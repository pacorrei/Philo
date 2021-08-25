/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	tmp;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	tmp = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
		nb++;
	}
	if (nb > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		tmp = tmp * 10 + str[i++] - '0';
	return (tmp * sign);
}

int	ft_verif_nbr(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '\0')
			return (1);
		while (av[i][j] != '\0')
		{
			if ((av[i][j] > '9' || av[i][j] < '0'))
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	verif_arg(int ac, char **av)
{
	int	i;

	if (ac < 5)
	{
		printf("Not enough argument.\n");
		return (1);
	}
	if (ac > 6)
	{
		printf("Too much argument.\n");
		return (1);
	}
	i = ft_verif_nbr(av);
	if (i == 1)
	{
		printf("Bad arguments.\n");
		return (1);
	}
	return (0);
}

int	verif_last_arg(char **av, int ac)
{
	int	i;

	if (av[5] != NULL && ac == 6)
	{
		i = ft_atoi(av[5]);
		if (i <= 0)
		{
			printf("The value must be above 0 for the last argument.\n");
			return (1);
		}
	}
	return (0);
}

long int	ft_get_time(void)
{
	struct timeval	time;
	long int		ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}
