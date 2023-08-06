/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:31:08 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/05 18:03:30 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int		Server::cmdPing(std::vector<std::string> args, Client &client)
{
	std::string pong = "PONG :" SERVERNAME " " + args[0] + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	_IP = args[0];
	std::string	banger = client.getNickname() + "!" + client.getUserName() + "@" + args[0];
	client.setBanger(banger);
	return (0);
}

// std::string	banger = ":" + client.getNickname() + "!" + client.getUserName() + "@" + args[0];
