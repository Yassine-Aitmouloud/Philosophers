/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/23 20:59:04 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&g_thread()->death);
	i = g_thread()->someone_died;
	pthread_mutex_unlock(&g_thread()->death);
	return (i);
}

void	create_philos(void)
{
	pthread_t	mon;
	int			i;

	mon = 0;
	i = 0;
	while (i < g_thread()->numbers)
	{
		g_thread()->philos[i].last_eat = get_time_ms();
		pthread_create(&g_thread()->philos[i].phi_id, NULL, &routine,
			&g_thread()->philos[i]);
		i++;
	}
	pthread_create(&mon, NULL, &monitor, NULL);
	pthread_join(mon, NULL);
}

void	regle(void)
{
	int	i;

	i = 0;
	while (i < g_thread()->numbers)
	{
		g_thread()->philos[i].checked = 0;
		g_thread()->philos[i].seat = i;
		g_thread()->philos[i].meals_eaten = 0;
		i++;
	}
}

int	get_start(void)
{
	int	i;

	i = 0;
	g_thread()->someone_died = 0;
	g_thread()->philos = malloc(sizeof(t_philos) * g_thread()->numbers);
	if (!g_thread()->philos)
		return (1);
	regle();
	g_thread()->forks = malloc(sizeof(pthread_mutex_t) * g_thread()->numbers);
	if (!g_thread()->forks)
		return (1);
	pthread_mutex_init(&g_thread()->printing, NULL);
	pthread_mutex_init(&g_thread()->eating_count, NULL);
	pthread_mutex_init(&g_thread()->death, NULL);
	pthread_mutex_init(&g_thread()->last_meal, NULL);
	pthread_mutex_init(&g_thread()->table, NULL);
	while (i < g_thread()->numbers)
		pthread_mutex_init(&g_thread()->forks[i++], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	int			i;

	i = 0;
	if (ac != 6 && ac != 5)
		return (1);
	check_avs(av);
	g_thread()->start = get_time_ms();
	if (get_start() == 0)
	{
		create_philos();
		while (i < g_thread()->numbers)
		{
			pthread_join(g_thread()->philos[i].phi_id, NULL);
			i++;
		}
	}
	clean_up();
	return (0);
}
