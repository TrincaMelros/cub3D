/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:24:41 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:15:07 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define ESC		53
# define MOVE_UP	13
# define MOVE_DOWN	1
# define MOVE_RIGHT	2
# define MOVE_LEFT	0

/**
 * # define KEY_PRESS_MASK 1L<<0
 * # define KEY_RELEASE_MASK 1L<<1

 * # define KEY_PRESS_EVENT 2
 * # define KEY_RELEASE_EVENT 3
 */

# define KEY_PRESS 1L
# define KEY_RELEASE 03
# define KEY_ESC 53
# define X_BUTTON_EXIT 17
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

#endif /*EVENTS_H*/