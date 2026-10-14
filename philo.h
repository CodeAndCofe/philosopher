/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:53:02 by aferryat          #+#    #+#             */
/*   Updated: 2025/07/04 01:00:23 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "unistd.h"
# include "sys/time.h"

typedef struct s_rule
{
	long			start_time;
	long			max_meal;
	long			t_die;
	long			t_sleep;
	long			t_eat;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;
	int				fail;
	int				philo_count;
	int				is_die;
}	t_rule;

typedef struct s_philo
{
	t_rule				*rule;
	pthread_mutex_t		fork;
	long				last_meal;
	int					is_starve;
	int					id;
	int					meals_eaten;
	struct s_philo		*next;
}	t_philo;

void		distroy_mutex_rule(t_rule *rule);
void		distroy_mutex_philo(t_philo *head);
int			create_pthread(t_rule *rule, t_philo *head, int i, pthread_t *f);
void		joiner_thread(pthread_t *f, int i, int count);
int			init_locker_forks(t_philo *head);
int			checker_mutex(t_rule *rule, t_philo *philo);
int			init_locker(t_rule *rule);
void		threads_start(t_rule *rule, t_philo *head, int count);
t_philo		*philo_init(t_philo *head);
long		time_in_ms(void);
long		ft_atoi(char *str);
void		free_philo(t_philo *ph);
void		*death_detector(void *arg);
void		manager(t_rule *rule);
void		taken_fork(t_philo *philo, t_rule *rule);
void		eating(t_philo *philo, t_rule *rule);
void		sleeping(t_philo *philo, t_rule *rule);
void		thinking(t_philo *philo, t_rule *rule);
int			is_died(t_rule	*rule);
void		*dining(void *arg);
t_philo		*create_philo_cyrcle(int count);
int			put_it_back(t_philo *philo);
int			grap_fork(t_rule *rule, t_philo *philo);
void		ft_usleep(long time, t_rule *rule);
#endif