/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:07:38 by haeem             #+#    #+#             */
/*   Updated: 2023/03/24 21:08:09 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

long long	min(long long a, long long b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

long long	max(long long a, long long b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

double	fmin(double a, double b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

double	fmax(double a, double b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
