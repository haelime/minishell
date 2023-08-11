/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:09:33 by haeem             #+#    #+#             */
/*   Updated: 2023/08/11 20:19:19 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ctrl+C Interrupt
void	sigint_handler(int signo);

// Ctrl+\ Interrupt
void	sigquit_handler(int signo);

// Ctrl+D Interrupt
void	sigterm_handler(int signo);

void	sigint_handler(int signo)
{
	(void)signo;
}

void	sigquit_handler(int signo)
{
	(void)signo;
}

void	sigterm_handler(int signo)
{
	(void)signo;
}
