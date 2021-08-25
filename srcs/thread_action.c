/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time)
{
	long int	current;
	long int	start;

	current = 0;
	start = ft_get_time();
	while (time > current - start)
	{
		usleep(100);
		current = ft_get_time();
	}
}

void	ft_eat2(t_philo *var)
{
	struct timeval	time;

	printf("%ld Philo %d has taken a fork\n", ft_get_time() - var->start_time[0],
		var->order + 1);
	printf("%ld Philo %d is eating\n", (ft_get_time() - var->start_time[0]),
		var->order + 1);
	pthread_mutex_unlock(var->write);
	var->eating = 1;
	gettimeofday(&time, NULL);
	var->last_meal = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	var->nbr_eat++;
	ft_usleep(var->time_eat);
	var->eating = 0;
	pthread_mutex_unlock(var->first_fork);
	pthread_mutex_unlock(var->second_fork);
}

void	ft_eat(t_philo *var)
{
	if (var->nbr_philo == 1)
		ft_usleep(var->time_die);
	pthread_mutex_lock(var->first_fork);
	pthread_mutex_lock(var->write);
	if (g_dead == 1 || g_meal_finish == var->nbr_philo)
	{
		pthread_mutex_unlock(var->first_fork);
		pthread_mutex_unlock(var->write);
		return ;
	}
	printf("%ld Philo %d has taken a fork\n", ft_get_time() - var->start_time[0],
		var->order + 1);
	pthread_mutex_unlock(var->write);
	pthread_mutex_lock(var->second_fork);
	pthread_mutex_lock(var->write);
	if (g_dead == 1 || g_meal_finish == var->nbr_philo)
	{
		pthread_mutex_unlock(var->first_fork);
		pthread_mutex_unlock(var->second_fork);
		pthread_mutex_unlock(var->write);
		return ;
	}
	ft_eat2(var);
}

void	ft_sleep(t_philo *var)
{
	pthread_mutex_lock(var->write);
	if (g_dead == 1 || g_meal_finish == var->nbr_philo)
	{
		pthread_mutex_unlock(var->write);
		return ;
	}
	printf("%ld Philo %d is sleeping\n", (ft_get_time() - var->start_time[0]),
		var->order + 1);
	pthread_mutex_unlock(var->write);
	ft_usleep(var->time_sleep);
}

void	ft_thinking(t_philo *var)
{
	pthread_mutex_lock(var->write);
	if (g_dead == 1 || g_meal_finish == var->nbr_philo)
	{
		pthread_mutex_unlock(var->write);
		return ;
	}
	printf("%ld Philo %d is thinking\n", (ft_get_time() - var->start_time[0]),
		var->order + 1);
	pthread_mutex_unlock(var->write);
	if (var->nbr_philo % 2 == 1)
		usleep(100);
}
