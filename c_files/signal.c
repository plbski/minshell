/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:14:36 by gvalente          #+#    #+#             */
/*   Updated: 2025/01/28 01:23:31 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	sigint_handler(int sig __attribute__((unused)))
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line ();
	rl_redisplay();
}

/**
 * @note setup CTRL-\. It does nothing but the prompt as to be redisplayed
 * no error possible
 * @attention 
 */
void	sigquit_handler(int sig __attribute__((unused)))
{
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @note Ctrl-d handler - must free stuff on quit
 * @attention Carefull not to create zombie processes on quit!
 * @todo Call function exit() and redirect to that function
 */
void	sigterm_handler(int sig __attribute__((unused)))
{
	return ;
}

void	setup_signal(int is_waiting)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_term;

	if (is_waiting)
		sa_int.sa_handler = SIG_IGN;
	else
		sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sa_term.sa_handler = sigterm_handler;
	if (is_waiting)
		sa_quit.sa_handler = SIG_IGN;
	else
		sa_quit.sa_handler = sigquit_handler;
	sa_term.sa_flags = 0;
	sigemptyset(&sa_term.sa_mask);
	sigaction(SIGTERM, &sa_term, NULL);
}
