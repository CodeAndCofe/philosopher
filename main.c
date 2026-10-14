/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferryat <aferryat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:56:52 by aferryat          #+#    #+#             */
/*   Updated: 2025/06/30 19:51:51 by aferryat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(t_rule *rule, char **arv)
{
	rule->fail = 0;
	rule->is_die = 0;
	rule->start_time = time_in_ms();
	rule->philo_count = ft_atoi(arv[1]);
	rule->t_die = ft_atoi(arv[2]);
	rule->t_eat = ft_atoi(arv[3]);
	rule->t_sleep = ft_atoi(arv[4]);
}

int	parse_input(char **arv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (arv[i])
	{
		if (arv[i][j] == '+')
			j++;
		while (arv[i][j])
		{
			if (arv[i][j] > '9' || arv[i][j] < '0')
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	main(int arc, char **arv)
{
	t_rule	rule;

	if (arc < 5 || arc > 6)
		return (printf("Invalid Input\n"), 1);
	if (parse_input(arv) == -1)
		return (printf("Invalid Input 'Should be valid Number'\n"), 1);
	init_rules(&rule, arv);
	if (arc == 6)
	{
		rule.max_meal = ft_atoi(arv[5]);
		if (rule.max_meal < 0)
			return (printf("Invalid Input\n"), 1);
	}
	else
		rule.max_meal = -1;
	if (rule.philo_count <= 0 || rule.t_die <= 59
		|| rule.t_eat <= 59 || rule.t_sleep <= 59)
		return (printf("Invalid arguments\n"), 1);
	if (rule.max_meal == 0)
		return (0);
	manager(&rule);
	if (rule.fail == 1)
		return (printf("philo : fails\n"), 1);
	return (0);
}
