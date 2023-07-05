/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:20:07 by msharifi          #+#    #+#             */
/*   Updated: 2023/07/03 17:56:50 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	Server::handleModeUser(std::vector<std::string> args, Client &client)
{
	if (!usedNickname(args[0]))
	{
		std::string answer = "401 " + client.getNickname() + " " + client.getNickname() + " :No suche nick/channel\r\n"; // ERR_NOSUCHNICK
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (args[0] != client.getNickname())
	{
		std::string answer = "502 " + client.getNickname() + " :Cant change mode for other users\r\n"; // ERR_USERSDONTMATCH
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	if (args[1].empty())
	{
		// printUserMode();
		return (0);
	}
	else
	{
		
	}
	return (0);
}
