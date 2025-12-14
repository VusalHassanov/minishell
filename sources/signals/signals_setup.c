/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:30:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/14 17:37:30 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when we are in main shell
void	setup_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

//everytime we pipe
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

//for heredoc input
void	setup_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_sigint);
}

void setup_dquote_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_dquote_sigint);
}