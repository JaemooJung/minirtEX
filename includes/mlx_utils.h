/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemung <jaemjung@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:01:10 by jaemjung          #+#    #+#             */
/*   Updated: 2022/06/13 22:22:37 by jaemung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "minirt.h"
# include "error.h"

void	init_mlx(t_mlx_info *info);
int		terminate(t_mlx_info *info);
int		key_hook(int keycode, t_mlx_info *info);

#endif
