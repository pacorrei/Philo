/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:15:22 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/01 04:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					nbr_philo;
	long int			time_die;
	int					time_eat;
	int					time_sleep;
	int					philo_eat;
	long int			*start_time;
	long int			last_meal;
	int					order;
	int					nbr_eat;
	int					eating;
	int					*creat;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*write;
}				t_philo;

int		g_dead;
int		g_meal_finish;
int		g_creat;

long int		ft_get_time(void);
int				ft_verif_nbr(char **av);
int				ft_atoi(const char *str);
int				verif_arg(int ac, char **av);
int				verif_last_arg(char **av, int ac);
void			ft_eat(t_philo *var);
void			ft_sleep(t_philo *var);
void			ft_thinking(t_philo *var);
void			ft_usleep(long int time);
void			*verif_thread(void *data);
void			*start_thread(void *p_data);
t_philo			*create_struct(t_philo *var, pthread_mutex_t *tab);
pthread_mutex_t	*create_mutex(int nbr_philo);
t_philo			*create_base_struct(char **av);
void			exit_thread(t_philo *var);

#endif