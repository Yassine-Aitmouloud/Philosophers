/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniki <aniki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/13 02:11:04 by aniki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    use_usleep(long duration_ms)
{
    long start = get_time_ms();
    while (get_time_ms() - start < duration_ms)
        usleep(100);
}

t_threads	*g_thread(void)
{
	static t_threads    infos = {0};

	return (&infos);
}

void	print_action(t_philos *philo, char *msg)
{
    long	timestamp;

    pthread_mutex_lock(&g_thread()->mute);
    timestamp = get_time_ms() - g_thread()->start;
    printf("%ld %d %s\n", timestamp, philo->seat + 1, msg);
    pthread_mutex_unlock(&g_thread()->mute);
}
void printnaam(t_philos *philos)
{
    print_action(philos, "is sleeping");
    use_usleep(g_thread()->sleeping);
}

void printfker(t_philos *philos)
{
    print_action(philos, "is thinking");
    use_usleep(100);
}

void take_the_forks(t_philos *philos)
{
	int left = philos->seat;
	int right = (philos->seat + 1) % g_thread()->numbers;
    
	if (left < right)
    {
        pthread_mutex_lock(&g_thread()->forks[left]);
        pthread_mutex_lock(&g_thread()->forks[right]);
    } 
    else
    {
        pthread_mutex_lock(&g_thread()->forks[right]);
        pthread_mutex_lock(&g_thread()->forks[left]);
    }
}

long	get_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void printkol(t_philos *philos)
{
    take_the_forks(philos);
    pthread_mutex_lock(&g_thread()->mute);
    philos->last_eat = get_time_ms();
    pthread_mutex_unlock(&g_thread()->mute);
    print_action(philos, "is eating");
    int left = philos->seat;
    int right = (philos->seat + 1) % g_thread()->numbers;
    use_usleep(g_thread()->eating);
    pthread_mutex_unlock(&g_thread()->forks[left]);
    pthread_mutex_unlock(&g_thread()->forks[right]);
}

void *routine(void *arg)
{
	t_philos *philo = (t_philos *)arg;
	if (philo->seat % 2 == 1)
		usleep(800);
	while (1)
	{
		printkol(philo);
		printnaam(philo);
		printfker(philo);
	}
	return NULL;
}

void *monitor(void *arg)
{
    int i;
    (void)arg;
    while (1)
    {
        i = 0;
        while (i < g_thread()->numbers)
        {
            pthread_mutex_lock(&g_thread()->mute);
            long now = get_time_ms();
            if (now - g_thread()->philos[i].last_eat > g_thread()->time_die)
            {
                printf("%ld %d died\n", now - g_thread()->start, i + 1);
                exit(0);
            }
            pthread_mutex_unlock(&g_thread()->mute);
            i++;
        }
        use_usleep(100);
    }
    return NULL;
}

int is_int(char *str)
{
    int i;
    i = 0;
    if (!str || !*str)
        return 1;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 1;
        i++;
    }
    return 0;
}

void check_avs(char **av)
{
    int i = 1;
    while (av[i])
    {
        if (is_int(av[i]) || atoi(av[i]) <= 0)
        {
            printf("Invalid argument: %s\n", av[i]);
            exit(1);
        }
        i++;
    }
    g_thread()->numbers = atoi(av[1]);
    g_thread()->time_die = atoi(av[2]);
    g_thread()->eating = atoi(av[3]);
    g_thread()->sleeping = atoi(av[4]);
}
int main(int ac, char **av)
{
    pthread_t mon;
    int i = 0;

    if (ac != 5)
        return 1;

    check_avs(av);
    g_thread()->philos = malloc(sizeof(t_philos) * g_thread()->numbers);
    g_thread()->original = g_thread()->philos;
    g_thread()->forks = malloc(sizeof(pthread_mutex_t) * g_thread()->numbers);
    while (i < g_thread()->numbers)
        pthread_mutex_init(&g_thread()->forks[i++], NULL);

    g_thread()->start = get_time_ms();
    i = 0;
    while (i < g_thread()->numbers)
    {
        g_thread()->philos[i].seat = i;
        g_thread()->philos[i].last_eat = get_time_ms();
        pthread_create(&g_thread()->philos[i].phi_id, NULL, &routine, &g_thread()->philos[i]);
        usleep(100);
        i++;
    }
    pthread_create(&mon, NULL, &monitor, NULL);
    pthread_join(mon, NULL);
    i = 0;
    while (i < g_thread()->numbers)
        pthread_join(g_thread()->original[i++].phi_id, NULL);

    return 0;
}
