/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:52:56 by aferryat          #+#    #+#             */
/*   Updated: 2025/07/03 21:28:09 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_rule *rule, t_philo *philo)
{
	pthread_mutex_lock(&rule->lock);
	if (time_in_ms() - philo->last_meal >= rule->t_die
		&& philo->is_starve == 1)
	{
		rule->is_die = 1;
		pthread_mutex_unlock(&rule->lock);
		pthread_mutex_lock(&rule->print_lock);
		printf("%ld %d died\n", time_in_ms() - rule->start_time, philo->id);
		pthread_mutex_unlock(&rule->print_lock);
		return ;
	}
	pthread_mutex_unlock(&rule->lock);
}

int	should_continue(t_rule *rule)
{
	int	f;

	f = -1;
	pthread_mutex_lock(&rule->lock);
	if (rule->is_die != 1 && rule->philo_count > 0 && rule->fail != 1)
		f = rule->philo_count;
	pthread_mutex_unlock(&rule->lock);
	return (f);
}

void	*death_detector(void *arg)
{
	int		i;
	int		is_continue;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		is_continue = should_continue(philo->rule);
		if (is_continue == -1)
			break ;
		i = 0;
		while (i < is_continue)
		{
			is_continue = should_continue(philo->rule);
			if (is_continue == -1)
				break ;
			checker(philo->rule, philo);
			philo = philo->next;
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	destroyer(t_rule *rule, t_philo *philo)
{
	t_philo	*wlk;

	wlk = philo->next;
	while (wlk != philo)
	{
		pthread_mutex_destroy(&wlk->fork);
		wlk = wlk->next;
	}
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&rule->lock);
	pthread_mutex_destroy(&rule->print_lock);
}

void	threads_start(t_rule *rule, t_philo *head, int count)
{
	pthread_t	deathkeeper;
	pthread_t	*f;
	int			created;

	f = malloc((count) * sizeof(pthread_t));
	if (f == NULL)
		return (free_philo(head));
	if (checker_mutex(rule, head) == -1)
		return (free_philo(head), free(f));
	created = create_pthread(rule, head, 0, f);
	if (created < 0)
		return (joiner_thread(f, 0, created * -1),
			destroyer(rule, head), free_philo(head), free(f));
	if (pthread_create(&deathkeeper, NULL, death_detector, head) != 0)
	{
		rule->fail = 1;
		return (joiner_thread(f, 0, count), destroyer(rule, head),
			free_philo(head), free(f));
	}
	joiner_thread(f, 0, count);
	pthread_join(deathkeeper, NULL);
	destroyer(rule, head);
	free_philo(head);
	free(f);
}
