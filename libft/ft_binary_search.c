/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:23 by haeem             #+#    #+#             */
/*   Updated: 2023/05/08 18:21:49 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

int	ft_binary_search(int arr[], int x, int low, int high)
{
	int	mid;

	if (high >= low)
	{
		mid = low + (high - low) / 2;
		if (arr[mid] == x)
			return (mid);
		if (arr[mid] > x)
			return (ft_binary_search(arr, x, low, mid - 1));
		return (ft_binary_search(arr, x, mid + 1, high));
	}
	return (-1);
}
