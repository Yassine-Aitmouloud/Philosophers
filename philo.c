/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/19 21:42:39 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    use_usleep(long duration)
{
    long start = get_time_ms();
    while (get_time_ms() - start < duration);
}
int is_died()
{
    int i = 0;
 
    pthread_mutex_lock(&g_thread()->death);
    i = g_thread()->someone_died;
    pthread_mutex_unlock(&g_thread()->death);
    return (i);
}

t_threads	*g_thread(void)
{
	static t_threads    infos;

	return (&infos);
}

void	print_action(t_philos *philo, char *msg)
{
    long	timestamp;
    timestamp = get_time_ms() - g_thread()->start;
    if (is_died())
        return ;
    pthread_mutex_lock(&g_thread()->printing);
    if (!is_died())
        printf("%ld %d %s\n", timestamp, philo->seat + 1, msg);
    write(1,&philo->seat,4);
    pthread_mutex_unlock(&g_thread()->printing);
}
void printnaam(t_philos *philos)
{
    if (is_died())
        return ;
    print_action(philos, "is sleeping");
    use_usleep(g_thread()->sleeping);
}

void printfker(t_philos *philos)
{
    if (is_died())
        return ;
    print_action(philos, "is thinking");
    if (philos->seat % 2 == 1)
        usleep(150);
}

void take_the_forks(t_philos *philos)
{
	int left = philos->seat;
	int right = (philos->seat + 1) % g_thread()->numbers;
    
	if (left < right)
    {
        pthread_mutex_lock(&g_thread()->forks[left]);
        print_action(philos, "take left fork");
        pthread_mutex_lock(&g_thread()->forks[right]);
        print_action(philos, "take right fork");
    } 
    else
    {
            pthread_mutex_lock(&g_thread()->forks[right]);
            print_action(philos, "take right fork");
            pthread_mutex_lock(&g_thread()->forks[left]);
            print_action(philos, "take left fork");
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
    if (is_died())
        return ;
    take_the_forks(philos);
    print_action(philos, "is eating");
    pthread_mutex_lock(&g_thread()->last_meal);
    philos->last_eat = get_time_ms();
    pthread_mutex_unlock(&g_thread()->last_meal);
    use_usleep(g_thread()->eating);
    philos->meals_eaten++;
    if (philos->checked == 0 && philos->meals_eaten >= g_thread()->must_eat)
    {
        pthread_mutex_lock(&g_thread()->eating_count);
        philos->checked = 1;
        pthread_mutex_unlock(&g_thread()->eating_count);
    }
    int left = philos->seat;
    int right = (philos->seat + 1) % g_thread()->numbers;
    pthread_mutex_unlock(&g_thread()->forks[right]);
    pthread_mutex_unlock(&g_thread()->forks[left]);
}

void *routine(void *arg)
{
	t_philos *philo = (t_philos *)arg;
    while(is_died() == 0)
    {
        printkol(philo);
        printnaam(philo);
        printfker(philo);
    }
    return NULL;
}
long get_last_meal(int i)
{
    long last_meal;
    pthread_mutex_lock(&g_thread()->last_meal);
    last_meal = g_thread()->philos[i].last_eat;
    pthread_mutex_unlock(&g_thread()->last_meal);
    return(last_meal);
}
int check_for_checked(int i)
{
    pthread_mutex_lock(&g_thread()->eating_count);
    if (g_thread()->philos[i].checked)
        return (pthread_mutex_unlock(&g_thread()->eating_count),1);
    return (pthread_mutex_unlock(&g_thread()->eating_count),0);        
}

int check_the_philos()
{
    int i = 0;
    
    while(i < g_thread()->numbers)
    {
        if (!check_for_checked(i))
            return (0);
        i++;
    }
    return (1);
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
            long now = get_time_ms();
            if (now - get_last_meal(i) > g_thread()->time_die)
            {
                print_action(&g_thread()->philos[i],"died");
                pthread_mutex_lock(&g_thread()->death);
                g_thread()->someone_died = 1;
                pthread_mutex_unlock(&g_thread()->death);
                return 0;
            }
            if (g_thread()->must_eat > 0)
            {
                if (check_the_philos())
                {
                    pthread_mutex_lock(&g_thread()->death);
                    g_thread()->someone_died = 1;
                    pthread_mutex_unlock(&g_thread()->death);
                    return NULL;
                }
            }
            i++;
        }
        use_usleep(1);
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
    if (av[5] == NULL)
        g_thread()->must_eat = -1;
    else
        g_thread()->must_eat = atoi(av[5]);
}
int main(int ac, char **av)
{
    pthread_t mon;
    int i = 0;

    if (ac != 6 && ac != 5)
        return 1;
    check_avs(av);
    g_thread()->someone_died = 0;
    pthread_mutex_init(&g_thread()->mute, NULL);
    pthread_mutex_init(&g_thread()->printing, NULL);
    pthread_mutex_init(&g_thread()->eating_count, NULL);  
    pthread_mutex_init(&g_thread()->death, NULL);  
    pthread_mutex_init(&g_thread()->last_meal, NULL);      
    g_thread()->philos = malloc(sizeof(t_philos) * g_thread()->numbers);
    g_thread()->forks = malloc(sizeof(pthread_mutex_t) * g_thread()->numbers);
    while (i < g_thread()->numbers)
        pthread_mutex_init(&g_thread()->forks[i++], NULL);
    g_thread()->start = get_time_ms();
    i = 0;
    while (i < g_thread()->numbers)
    {
        g_thread()->philos[i].meals_eaten = 0;
        g_thread()->philos[i].checked = 0;
        g_thread()->philos[i].seat = i;
        g_thread()->philos[i].last_eat = get_time_ms();
        pthread_create(&g_thread()->philos[i].phi_id, NULL, &routine, &g_thread()->philos[i]);
        i++;
    }
    pthread_create(&mon, NULL, &monitor, NULL);
    pthread_join(mon, NULL);
    i = 0;
    while (i < g_thread()->numbers)
    {
        pthread_join(g_thread()->philos[i].phi_id, NULL);
        i++;
    }
    free (g_thread()->philos);
    free (g_thread()->forks);
    return 0;
}
