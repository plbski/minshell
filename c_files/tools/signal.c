/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:14:36 by gvalente          #+#    #+#             */
/*   Updated: 2025/02/25 22:18:20 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../msh.h"

static void	sigint_handler(int sig __attribute__((unused)))
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line ();
	rl_redisplay();
}

static void	sigquit_handler(int sig __attribute__((unused)))
{
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_handler_heredoc(int sig)
{
	g_quit_in_heredoc = sig;
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
	sa_term.sa_handler = SIG_IGN;
	sa_term.sa_flags = 0;
	sigemptyset(&sa_term.sa_mask);
	sigaction(SIGTERM, &sa_term, NULL);
}
