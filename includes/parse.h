/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:23:47 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/28 22:36:37 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"

typedef struct s_p_node
{
	int				id;
	t_vec			coord;
	t_vec			normal;
	int				color[3];
	double			geometric[2];
	int				etc[2];
	int				is_transformed;
	t_vec			transform[3];
	struct s_p_node	*next;
}	t_p_node;

# define A 1
# define C 2
# define L 3
# define SP 4
# define PL 5
# define CY 6
# define HY 7

#endif