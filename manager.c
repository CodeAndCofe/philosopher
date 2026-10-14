/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:06:55 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/24 16:23:13 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rule(t_philo *head, t_rule *rule)
{
	t_philo	*wlk;

	wlk = head;
	while (1)
	{
		wlk->last_meal = rule->start_time;
		wlk->rule = rule;
		wlk = wlk->next;
		if (wlk == head)
			break ;
	}
}

void	manager(t_rule *rule)
{
	t_philo	*head;

	head = create_philo_cyrcle(rule->philo_count);
	if (head == NULL)
		return ;
	init_rule(head, rule);
	threads_start(rule, head, rule->philo_count);
}
