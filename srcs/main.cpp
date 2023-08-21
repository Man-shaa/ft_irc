/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:26 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/21 18:29:41 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <stdlib.h>
#include <ctype.h>

Server server;

void fun(int sig)
{
	(void)sig;
	server.removeExit();
	exit(1) ;
}

int checkArg(char **av)
{
	//check that the port number is in digits and valid
	for (size_t i = 0; i < strlen(av[1]); i++)
		if (!isdigit(av[1][i]))
			return (0);
	if ((atoi(av[1]) >= 0 && atol(av[1]) < 1024) || atol(av[1]) > 65535)
		return (0);
	return(1);
}

int main(int ac, char **av) 
{
	if (ac != 3)
		return (std::cerr << "tuto: ./ft_irc <port> <password>" << std::endl, 1);
	if (!checkArg(av))
		return (std::cerr << "Incorrect port or invalid port" << std::endl, 0);
	signal(SIGINT, fun);
	server.start(atoi(av[1]), std::string(av[2]));
	return (0);
}
