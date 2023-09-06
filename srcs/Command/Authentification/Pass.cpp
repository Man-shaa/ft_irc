/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:28:21 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/09/06 21:30:18 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::cmdPass(std::vector<std::string> args, Client &client)
{
	if (args[0] != _password)
	{
		std::string	badPass = "464 " + client.getNickname() + " :Password incorrect\r\n";
		send(client.getSocket(), badPass.c_str(), badPass.size(), 0);
		std::string	quit = "ERROR Closing Link: 127.0.0.1 (Bad Password)\r\n";
		send(client.getSocket(), quit.c_str(), quit.size(), 0);
		close(client.getSocket());
		removeClient(client.getSocket());
		return (1);
	}
	if (client.getNickname() != "bot")
		client.setStatus(PASSWORD);
	return (0);
}
