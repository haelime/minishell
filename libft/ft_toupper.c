/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:54:04 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:38 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int ch)
{
	if ('a' <= ch && ch <= 'z')
		ch = ch - 32;
	return (ch);
}
