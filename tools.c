/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:11:42 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/25 15:23:14 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long		i;
	int			sign;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	free_philo(t_philo *ph)
{
	t_philo	*head;
	t_philo	*temp;

	head = ph;
	ph = ph->next;
	while (ph != head)
	{
		temp = ph;
		ph = ph->next;
		free(temp);
	}
	free(head);
}

static void	free_philo_f(t_philo *ph)
{
	t_philo	*temp;

	while (ph != NULL)
	{
		temp = ph;
		ph = ph->next;
		free(temp);
	}
}

t_philo	*philo_init(t_philo *head)
{
	int		i;
	t_philo	*wlk;

	head->id = 1;
	head->last_meal = 0;
	head->meals_eaten = 0;
	head->is_starve = 1;
	wlk = head->next;
	i = 2;
	while (wlk != head)
	{
		wlk->id = i;
		head->last_meal = 0;
		head->meals_eaten = 0;
		head->is_starve = 1;
		i++;
		wlk = wlk->next;
	}
	return (head);
}

t_philo	*create_philo_cyrcle(int count)
{
	int		i;
	t_philo	*head;
	t_philo	*wlk;

	i = 1;
	head = malloc(sizeof (t_philo));
	if (head == NULL)
		return (NULL);
	wlk = head;
	while (i < count)
	{
		wlk->next = malloc (sizeof (t_philo));
		if (wlk->next == NULL)
			return (free_philo_f(head), NULL);
		wlk = wlk->next;
		i++;
	}
	wlk->next = head;
	head = philo_init(head);
	return (head);
}
