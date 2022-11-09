/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:15:30 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/25 16:16:49 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Adds b to a
 * 
 * @param a 
 * @param b 
 * @return t_vector2 
 */
t_vector2	ft_vector2_add(t_vector2 a, t_vector2 b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	return (a);
}