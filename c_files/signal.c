/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:14:36 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/01 01:23:25 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	sigint_handler(int sig __attribute__((unused)))
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
static void	sigquit_handler(int sig __attribute__((unused)))
{
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @note Ctrl-d handler - must free stuff on quit
 * @attention Carefull not to create zombie processes on quit!
 * @todo Call function exit() and redirect to that function
 */
static void	sigterm_handler(int sig __attribute__((unused)))
{
	return ;
}

static void	sigint_handler_heredoc(int sig __attribute__((unused)))
{
	g_quit_in_heredoc = 1;
	reset_readline();
}

void	setup_signal(int is_waiting, int is_heredoc)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_term;

	if (is_heredoc)
		sa_int.sa_handler = sigint_handler_heredoc;
	else if (is_waiting)
		sa_int.sa_handler = SIG_IGN;
	else
		sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	if (is_waiting || is_heredoc)
		sa_quit.sa_handler = SIG_IGN;
	else
		sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sa_term.sa_handler = sigterm_handler;
	sa_term.sa_flags = 0;
	sigemptyset(&sa_term.sa_mask);
	sigaction(SIGTERM, &sa_term, NULL);
}
