/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:59:44 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/30 19:49:35 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_process(t_philo *philo, t_rule *rule)
{
	eating(philo, rule);
	pthread_mutex_lock(&rule->lock);
	philo->last_meal = time_in_ms();
	philo->meals_eaten++;
	philo->is_starve = 0;
	pthread_mutex_unlock(&rule->lock);
	ft_usleep(rule->t_eat, rule);
	if (is_died(rule) == 1)
		return (put_it_back(philo), -1);
	if (philo->meals_eaten == rule->max_meal)
	{
		pthread_mutex_lock(&rule->lock);
		rule->philo_count--;
		pthread_mutex_unlock(&rule->lock);
		return (put_it_back(philo), -1);
	}
	if (is_died(rule) == 1)
		return (put_it_back(philo), -1);
	pthread_mutex_lock(&rule->lock);
	philo->is_starve = 1;
	pthread_mutex_unlock(&rule->lock);
	put_it_back(philo);
	if (is_died(rule) == 1)
		return (-1);
	return (1);
}

int	process(t_philo *philo, t_rule *rule)
{
	if (eat_process(philo, rule) != 1)
		return (-1);
	sleeping(philo, rule);
	if (is_died(rule) == 1)
		return (-1);
	ft_usleep(rule->t_sleep, rule);
	if (is_died(rule) == 1)
		return (-1);
	thinking(philo, rule);
	if (is_died(rule) == 1)
		return (-1);
	return (1);
}

void	*dining(void *arg)
{
	t_philo	*philo;
	t_rule	*rule;

	philo = (t_philo *) arg;
	rule = philo->rule;
	if (philo->id % 2 == 1)
		usleep(1500);
	while (is_died(rule) == 0)
	{
		pthread_mutex_lock(&rule->lock);
		if (rule->fail == 1)
			return (pthread_mutex_unlock(&rule->lock), NULL);
		pthread_mutex_unlock(&rule->lock);
		if (grap_fork(rule, philo) == -1)
			return (NULL);
		if (is_died(rule) == 1)
			return (put_it_back(philo), NULL);
		if (process(philo, rule) == -1)
			return (NULL);
		if (is_died(rule) == 1)
			return (NULL);
	}
	return (NULL);
}
