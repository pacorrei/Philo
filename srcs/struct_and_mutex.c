/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_and_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_struct2(t_philo *var)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	tmp->nbr_philo = var->nbr_philo;
	tmp->order = var->order;
	tmp->philo_eat = var->philo_eat;
	tmp->start_time = var->start_time;
	tmp->last_meal = var->last_meal;
	tmp->time_die = var->time_die;
	tmp->time_eat = var->time_eat;
	tmp->time_sleep = var->time_sleep;
	tmp->nbr_eat = var->nbr_eat;
	tmp->creat = var->creat;
	tmp->eating = 0;
	return (tmp);
}

t_philo	*create_struct(t_philo *var, pthread_mutex_t *tab)
{
	t_philo	*tmp;

	tmp = create_struct2(var);
	if (var->order == 0)
	{
		tmp->first_fork = &tab[var->order];
		tmp->second_fork = &tab[var->nbr_philo - 1];
	}
	else if (var->order % 2 != 0)
	{
		tmp->first_fork = &tab[var->order - 1];
		tmp->second_fork = &tab[var->order];
	}
	else if (var->order % 2 == 0)
	{
		tmp->second_fork = &tab[var->order - 1];
		tmp->first_fork = &tab[var->order];
	}
	tmp->write = var->write;
	return (tmp);
}

pthread_mutex_t	*create_mutex(int nbr_philo)
{
	pthread_mutex_t	*ret;
	int				i;

	ret = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	i = 0;
	while (i < nbr_philo)
	{
		pthread_mutex_init(&ret[i], NULL);
		pthread_mutex_unlock(&ret[i]);
		i++;
	}
	return (ret);
}

t_philo	*create_base_struct(char **av)
{
	t_philo	*var;

	var = malloc(sizeof(t_philo));
	var->nbr_philo = ft_atoi(av[1]);
	var->time_die = ft_atoi(av[2]);
	var->time_eat = ft_atoi(av[3]);
	var->time_sleep = ft_atoi(av[4]);
	var->philo_eat = -1;
	if (av[5] != NULL)
		var->philo_eat = ft_atoi(av[5]);
	var->order = 0;
	var->nbr_eat = 0;
	var->creat = malloc(sizeof(int) * 1);
	var->creat[0] = 0;
	var->start_time = malloc(sizeof(long int) * 1);
	var->start_time[0] = ft_get_time();
	var->last_meal = var->start_time[0];
	var->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(var->write, NULL);
	pthread_mutex_unlock(var->write);
	g_dead = 0;
	g_creat = 0;
	g_meal_finish = 0;
	return (var);
}
