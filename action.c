/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:52:41 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/30 19:49:32 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taken_fork(t_philo *philo, t_rule *rule)
{
	long	t;

	if (is_died(rule) == 1)
		return ;
	t = time_in_ms() - rule->start_time;
	pthread_mutex_lock(&rule->print_lock);
	if (is_died(rule) != 1)
		printf("%ld %d has taken a fork\n", t, philo->id);
	pthread_mutex_unlock(&rule->print_lock);
}

void	eating(t_philo *philo, t_rule *rule)
{
	long	t;

	if (is_died(rule) == 1)
		return ;
	t = time_in_ms() - rule->start_time;
	pthread_mutex_lock(&rule->print_lock);
	if (is_died(rule) != 1)
		printf("%ld %d is eating\n", t, philo->id);
	pthread_mutex_unlock(&rule->print_lock);
}

void	sleeping(t_philo *philo, t_rule *rule)
{
	long	t;

	if (is_died(rule) == 1)
		return ;
	t = time_in_ms() - rule->start_time;
	pthread_mutex_lock(&rule->print_lock);
	if (is_died(rule) != 1)
		printf("%ld %d is sleeping\n", t, philo->id);
	pthread_mutex_unlock(&rule->print_lock);
}

void	thinking(t_philo *philo, t_rule *rule)
{
	long	t;

	if (is_died(rule) == 1)
		return ;
	t = time_in_ms() - rule->start_time;
	pthread_mutex_lock(&rule->print_lock);
	if (is_died(rule) != 1)
		printf("%ld %d is thinking\n", t, philo->id);
	pthread_mutex_unlock(&rule->print_lock);
}
