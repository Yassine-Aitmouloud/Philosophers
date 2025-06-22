/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:13:33 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/22 21:48:20 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printnaam(t_philos *philos)
{
	print_action(philos, "is sleeping");
	use_usleep(g_thread()->sleeping);
}

void	printfker(t_philos *philos)
{
	print_action(philos, "is thinking");
	if (g_thread()->even_odd)
	{
		if (!is_died() && g_thread()->eating > g_thread()->sleeping)
			usleep(g_thread()->eating - g_thread()->sleeping);
		usleep(1000);
	}
}

void	printkol(t_philos *philos)
{
	int left;
	int right;

	if (is_died())
		return ;
	take_the_forks(philos);
	print_action(philos, "is eating");
	pthread_mutex_lock(&g_thread()->last_meal);
	philos->last_eat = get_time_ms();
	pthread_mutex_unlock(&g_thread()->last_meal);
	// philos->meals_eaten++;
	// if (philos->checked == 0 && philos->meals_eaten >= g_thread()->must_eat)
	// {
	// 	pthread_mutex_lock(&g_thread()->eating_count);
	// 	philos->checked = 1;
	// 	pthread_mutex_unlock(&g_thread()->eating_count);
	// }
	use_usleep(g_thread()->eating);
	left = philos->seat;
	right = (philos->seat + 1) % g_thread()->numbers;
	unlock_forks(right, left, philos);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->seat % 2 && g_thread()->even_odd == 0)
		usleep(1000);
	while (!is_died())
	{
		printkol(philo);
		printnaam(philo);
		printfker(philo);
	}
	return (NULL);
}

void	print_action(t_philos *philo, char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - g_thread()->start;
	pthread_mutex_lock(&g_thread()->printing);
	if (!is_died())
		printf("%ld %d %s\n", timestamp, philo->seat + 1, msg);
	pthread_mutex_unlock(&g_thread()->printing);
}