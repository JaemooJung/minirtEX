/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjung <jaemjung@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:31:11 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/10 17:40:23 by jaemjung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	error(const char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}
