/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:54:12 by haeem             #+#    #+#             */
/*   Updated: 2022/11/17 00:32:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int ch)
{
	if (65 <= ch && ch <= 90)
		ch = ch + 32;
	return (ch);
}
