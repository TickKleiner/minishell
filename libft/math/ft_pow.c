/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:50:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/08/16 18:51:17 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double n, double pow)
{
	double res;

	res = 1;
	while (pow--)
		res *= n;
	return (res);
}
