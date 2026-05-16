/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:24:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/16 18:39:49 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_god_struct;
struct	s_single_philo;

typedef struct s_shit_to_free
{
	void					*shit;
	struct s_shit_to_free	*next;
}							t_shit_to_free;

typedef struct s_god_struct
{
	t_shit_to_free			*shit_list;
	int						no_phil;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						no_o_t_e_p_m_eat;
	int						threads_created;
	int						forks_initialized;
	long long				start_time;
	pthread_mutex_t			simul_ready_mutex;
	int						ready;
	pthread_mutex_t			simul_ended_mutex;
	int						simul_ended;
	pthread_t				*threads;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			*forks;
	pthread_mutex_t			philo_add_mutex;
	struct s_single_philo	*philos;
}							t_god_struct;

typedef struct s_single_philo
{
	t_god_struct			*p_god;
	int						status;
	int						id;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						no_o_t_e_p_m_eat;
	pthread_mutex_t			time_last_meal_mutex;
	long long				time_last_meal;
	pthread_mutex_t			times_eaten_mutex;
	int						times_eaten;
	int						group;
	int						is_alternating;
	pthread_mutex_t			*fork_left;
	pthread_mutex_t			*fork_right;
	struct s_single_philo	*next;
}							t_single_philo;

enum						e_philo_status
{
	NOT_INIT = 0,
	INIT,
	SLEEPING,
	THINKING,
	FORK_TAKEN,
	HUNGRY,
	EATING,
	DEAD
};

enum
{
	RET_OK = 0,
	ERROR_SOFT = -1,
	ERROR_HARD = -2
};

enum
{
	GROUP_ODD,
	GROUP_EVEN
};

// debug.c
void						print_p_init(t_god_struct *p_init);
void						print_philo_forks(t_single_philo *philo);
void						say_hello(t_single_philo *philo);

// input_check.c
int							check_input(int argc, char **argv);
int							zero_check(t_god_struct *p_god);

// init.c
t_god_struct				*create_god_struct(char **argv);
t_single_philo				*init_philo_struct(t_god_struct *p_god, int i);

// init_mutexes.c
int							init_global_mutexes(t_god_struct *p_god);
int							init_philo_mutexes(t_single_philo *philo);
int							initialize_everything(t_god_struct *p_god);

// ft_atoi.c
int							ft_atoi(char *arg);

// ft_calloc.c
void						*ft_calloc(size_t nmemb, size_t size);

// time.c
long long					return_time_in_ms(void);
long long					return_delta_time(t_god_struct *p_god);
void						ft_usleep(long usec, t_single_philo *philo);
// threads.c
int							create_philo_threads(t_god_struct *p_god);
void						wait_for_philo_threads(t_god_struct *p_god);

// routine.c
void						*philo_routine(void *arg);
int							update_status_one_philo(t_single_philo *philo);
int							update_status_all(t_god_struct *p_god);

// forks.c
int							take_left_fork(t_single_philo *philo);
int							take_right_fork(t_single_philo *philo);
void						put_down_left_fork(t_single_philo *philo);
void						put_down_right_fork(t_single_philo *philo);

// philo_moves.c
void						wait_until_ready(t_god_struct *p_god);
int							eat(t_single_philo *philo);
int							sleeep(t_single_philo *philo);
int							think(t_single_philo *philo);
// print_master.c
void						print_status(t_god_struct *p_god, int event,
								int id);

// print_slave.c
void						print_status_fork(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_eating(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_sleeping(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_thinking(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_died(t_god_struct *p_god,
								long long timestamp, int id);

// cleanup.c
void						cleanup_everything(t_god_struct *p_god);
int							add_to_sl(t_shit_to_free **shit_list, void *elem);
void						destroy_global_mutexes(t_god_struct *p_god);

// getters.c
int							get_simul_ready(t_god_struct *p_god);
int							get_end_simul(t_god_struct *p_god);
long long					get_t_last_meal(t_single_philo *philo);
int							get_times_eaten(t_single_philo *philo);

// setters.c
void						set_simul_ready(t_god_struct *p_god);
void						set_end_simul(t_god_struct *p_god);
void						set_t_last_meal(t_single_philo *philo,
								long long time);
void						increment_times_eaten(t_single_philo *philo);

#endif