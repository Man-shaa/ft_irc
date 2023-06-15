/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:26 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/15 18:44:39 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <stdlib.h>

int main(int ac, char **av) 
{
	Server server;
	if (ac == 3)
	{
		server.start(atoi(av[1]));
	}
	return 0;
}
