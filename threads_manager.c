/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:56:25 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/25 16:14:09 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_pthread(t_rule *rule, t_philo *head, int i, pthread_t *f)
{
	int	count;

	count = rule->philo_count;
	while (i < count)
	{
		if (pthread_create(&f[i], NULL, dining, head) != 0)
		{
			rule->fail = 1;
			return (i * -1);
		}
		head = head->next;
		i++;
	}
	return (0);
}

void	joiner_thread(pthread_t *f, int i, int count)
{
	while (i < count)
	{
		pthread_join(f[i], NULL);
		i++;
	}
}

void	distroy_mutex_philo(t_philo *head)
{
	t_philo	*wlk;

	pthread_mutex_destroy(&head->fork);
	wlk = head->next;
	while (wlk != head)
	{
		pthread_mutex_destroy(&wlk->fork);
		wlk = wlk->next;
	}
}

void	distroy_mutex_rule(t_rule *rule)
{
	pthread_mutex_destroy(&rule->lock);
	pthread_mutex_destroy(&rule->print_lock);
}
