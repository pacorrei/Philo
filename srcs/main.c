/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *var, pthread_t *thread_philo, t_philo **copy)
{
	free(copy);
	free(thread_philo);
	pthread_mutex_destroy(var->write);
	free(var->write);
	free(var->start_time);
	free(var->creat);
	free(var);
	return ;
}

void	verif_end(t_philo *var, pthread_mutex_t	*tab, pthread_t	*thread_philo
, t_philo **copy)
{
	int	i;

	i = 0;
	while (i < var->nbr_philo)
	{
		pthread_join(thread_philo[i], NULL);
		i++;
	}
	while (i < var->nbr_philo)
	{
		pthread_mutex_destroy(&tab[i]);
		i++;
	}
	free(tab);
	i = 0;
	while (i < var->order)
	{
		free(copy[i]);
		i++;
	}
	free_all(var, thread_philo, copy);
	return ;
}

void	launch_thread(t_philo *var, pthread_t *thread_philo, t_philo **copy)
{
	while (var->order < var->nbr_philo)
	{
		pthread_create(& thread_philo[var->order], NULL, start_thread,
			 copy[var->order]);
		var->order++;
	}
	while (g_creat != var->nbr_philo)
	{
		usleep(100);
	}
	var->start_time[0] = ft_get_time();
	var->creat[0] = 1;
	return ;
}

int	main(int ac, char **av)
{
	t_philo			*var;
	t_philo			**copy;
	pthread_t		*thread_philo;
	pthread_mutex_t	*tab;
	int				i;

	i = verif_arg(ac, av);
	i += verif_last_arg(av, ac);
	if (i == 1)
		return (0);
	var = create_base_struct(av);
	tab = create_mutex(var->nbr_philo);
	thread_philo = malloc(sizeof(pthread_t) * var->nbr_philo);
	copy = malloc(sizeof(pthread_t) * var->nbr_philo);
	while (var->order < var->nbr_philo)
	{
		copy[var->order] = create_struct(var, tab);
		var->order++;
	}
	var->order = 0;
	launch_thread(var, thread_philo, copy);
	verif_end(var, tab, thread_philo, copy);
	return (0);
}
