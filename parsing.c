/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:19:35 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/26 15:42:32 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > __INT_MAX__)
			return (0);
		i++;
	}
	return ((int)(result));
}

void	check_avs(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_int(av[i]) || ft_atoi(av[i]) <= 0)
		{
			printf("Invalid argument: %s\n", av[i]);
			exit(1);
		}
		i++;
	}
	g_thread()->odd = 0;
	g_thread()->numbers = ft_atoi(av[1]);
	g_thread()->time_die = ft_atoi(av[2]);
	g_thread()->eating = ft_atoi(av[3]);
	g_thread()->sleeping = ft_atoi(av[4]);
	if (av[5] == NULL)
		g_thread()->must_eat = -1;
	else
		g_thread()->must_eat = atoi(av[5]);
	if (g_thread()->numbers % 2 == 1)
		g_thread()->odd = 1;
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	use_usleep(long duration)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration && !is_died())
		usleep(500);
}
