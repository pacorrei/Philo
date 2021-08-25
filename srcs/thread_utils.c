/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_thread(t_philo *var)
{
	pthread_mutex_lock(var->write);
	if (g_dead == 1)
	{
		pthread_mutex_unlock(var->write);
		return ;
	}
	g_dead = 1;
	printf("%ld Philo %d is dead\n", ft_get_time() - var->start_time[0],
		var->order + 1);
	pthread_mutex_unlock(var->write);
	return ;
}

int	verif_meal(t_philo *var, int verif)
{
	if (var->nbr_eat >= var->philo_eat && verif == 0
		&& var->philo_eat != -1)
	{
		g_meal_finish++;
		return (1);
	}
	return (0);
}

void	*verif_thread(void *data)
{
	t_philo	*var;
	int		verif;

	var = data;
	verif = 0;
	while (var->creat[0] == 0)
	{
		usleep(100);
	}
	var->last_meal = var->start_time[0];
	while (g_dead != 1 && g_meal_finish < var->nbr_philo)
	{
		if (ft_get_time() - var->last_meal >= var->time_die && var->eating == 0)
		{
			exit_thread(var);
			return (NULL);
		}
		if (verif == 0)
			verif = verif_meal(var, verif);
	}
	return (NULL);
}

void	*start_thread(void *p_data)
{
	t_philo		*var;
	pthread_t	philo_fils;
	int			verif;

	var = p_data;
	verif = 0;
	pthread_create(& philo_fils, NULL, verif_thread, var);
	while (var->creat[0] == 0)
	{
		if (verif == 0)
		{
			verif = 1;
			g_creat++;
		}
		usleep(100);
	}
	var->last_meal = var->start_time[0];
	while (g_dead == 0 && g_meal_finish < var->nbr_philo)
	{
		ft_eat(var);
		ft_sleep(var);
		ft_thinking(var);
	}
	pthread_join(philo_fils, NULL);
	return (NULL);
}
