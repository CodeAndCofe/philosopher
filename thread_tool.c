/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:03:42 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/30 19:49:50 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_rule *rule)
{
	int	ret;

	pthread_mutex_lock(&rule->lock);
	ret = rule->is_die;
	pthread_mutex_unlock(&rule->lock);
	return (ret);
}

void	ft_usleep(long time, t_rule *rule)
{
	long	current;

	current = time_in_ms();
	while (time_in_ms() - current < time)
	{
		pthread_mutex_lock(&rule->lock);
		if (rule->is_die == 1)
		{
			pthread_mutex_unlock(&rule->lock);
			return ;
		}
		pthread_mutex_unlock(&rule->lock);
		usleep(100);
	}
}

int	put_it_back(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (1);
}

int	grap_fork(t_rule *rule, t_philo *philo)
{
	if (is_died(rule) == 1)
		return (-1);
	pthread_mutex_lock(&philo->fork);
	if (is_died(rule) == 1)
		return (pthread_mutex_unlock(&philo->fork), -1);
	taken_fork(philo, rule);
	if (is_died(rule) == 1)
		return (pthread_mutex_unlock(&philo->fork), -1);
	if (philo->next->id == philo->id)
	{
		while (1)
			if (is_died(rule) == 1)
				return (pthread_mutex_unlock(&philo->fork), -1);
	}
	pthread_mutex_lock(&philo->next->fork);
	if (is_died(rule) == 1)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), -1);
	taken_fork(philo, rule);
	if (is_died(rule) == 1)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), -1);
	return (1);
}
