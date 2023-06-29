/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:26 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/29 16:32:38 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <stdlib.h>
#include <ctype.h>

int checkArg(char **av)
{
	//check that the port number is in digits and valid
	for (size_t i = 0; i < strlen(av[1]); i++)
		if (!isdigit(av[1][i]))
			return (0);
	if ((atoi(av[1]) >= 0 && atoi(av[1]) < 1024) || atoi(av[1]) > 65535)
		return (0);
	return(1);
}

int main(int ac, char **av) 
{
	Server server;
	if (ac != 3)
		return (std::cout << "tuto: ./ft_irc <port> <password>" << std::endl, 1);
	if (!checkArg(av))
		return (std::cout << "Incorrect port or invalid port" << std::endl, 0);
	server.start(atoi(av[1]), std::string(av[2]));
	return (0);
}
