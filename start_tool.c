/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:28:03 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/30 19:29:29 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_locker(t_rule *rule)
{
	if (pthread_mutex_init(&rule->lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&rule->print_lock, NULL) != 0)
		return (-2);
	return (1);
}

int	init_locker_forks(t_philo *head)
{
	int		i;
	t_philo	*wlk;

	wlk = head->next;
	i = 1;
	if (pthread_mutex_init(&head->fork, NULL) != 0)
		return (0);
	while (wlk != head)
	{
		if (pthread_mutex_init(&wlk->fork, NULL) != 0)
			return (i * -1);
		wlk = wlk->next;
		i++;
	}
	return (i);
}

int	checker_mutex(t_rule *rule, t_philo *philo)
{
	int	res;

	res = init_locker(rule);
	if (res == -1)
		return (-1);
	if (res == -2)
		return (pthread_mutex_destroy(&rule->lock), -1);
	res = init_locker_forks(philo);
	if (res < 0)
	{
		res *= -1;
		res -= 1;
		while (res >= 0)
		{
			pthread_mutex_destroy(&philo->fork);
			philo = philo->next;
			res--;
		}
		pthread_mutex_destroy(&rule->lock);
		pthread_mutex_destroy(&rule->print_lock);
		return (-1);
	}
	return (1);
}
