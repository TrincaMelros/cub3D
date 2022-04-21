/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:24:41 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/21 23:29:26 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/*key hooks*/
/** 
 * Already defined in mlx.h <------------
 *  enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}; */

/**
 * # define KEY_PRESS_MASK 1L<<0
 * # define KEY_RELEASE_MASK 1L<<1

 * # define KEY_PRESS_EVENT 2
 * # define KEY_RELEASE_EVENT 3
 */

# define KEY_PRESS 1L
# define KEY_ESC 53
# define X_BUTTON_EXIT 17
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

#endif /*EVENTS_H*/