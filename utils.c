/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:08 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/26 15:42:57 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_death(void)
{
	int	j;

	pthread_mutex_lock(&g_thread()->death);
	j = g_thread()->someone_died;
	pthread_mutex_unlock(&g_thread()->death);
	return (j);
}

t_threads	*g_thread(void)
{
	static t_threads	infos;

	return (&infos);
}

void	one_philo(void)
{
	pthread_mutex_lock(&g_thread()->forks[0]);
	print_action(&g_thread()->philos[0], "take the left fork");
	use_usleep(g_thread()->time_die);
	pthread_mutex_unlock(&g_thread()->forks[0]);
}
