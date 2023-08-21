/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:22:15 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/08 18:11:02 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "cstdlib"
#include <time.h>

Bot::Bot() : Client()
{
}

Bot::Bot(int socketFd, std::string nickname) : Client(socketFd, nickname)
{
}


Bot::Bot( Bot const &copy )
{
	*this = copy;
}

Bot::~Bot()
{
}

void	Bot::sendHelp(Channel &channel)	{
	std::string msg = ":botte PRIVMSG " + channel.getName();
	msg += " :List of commands :\r\n";
	msg += "?help : get the list of commands\r\n";
	msg += "?joke : tell a joke\r\n";
	msg += "?hi : say hi\r\n";
	msg += "\r\n";
	std::cout << msg << std::endl;
	channel.sendMsgNoBot(msg, *this);
}

void	Bot::sendJoke(Channel &channel)	{
	std::string msg = ":botte PRIVMSG " + channel.getName();
	int random;
	srand (time(NULL));
	random = rand() % 5;
	
	switch (random)	{
		case(0):
			msg += " :What did the evil chicken lay? Deviled eggs.";
			break;
		case(1):
			msg += " :How do you make holy water? You boil the hell out of it.";
			break;
		case(2):
			msg += " :What sound does a witch’s car make? Broom broom!.";
			break;
		case(3):
			msg += " :What do you call a dog that can do magic? A Labracabrador.";
			break;
		case(4):
			msg += " :What do you call a fish with no eye? A fsh.";
			break;
		default:
			msg += " :Achem ...";
			break;
	}
	msg += "\r\n";
	channel.sendMsgNoBot(msg, *this);
}

void	Bot::sendHi(Channel &channel)	{
	std::string msg = ":botte PRIVMSG " + channel.getName();
	msg += " :Hi !";
	msg += "\r\n";
	channel.sendMsgNoBot(msg, *this);
}

void	Bot::sendError(Channel &channel)	{
	std::string msg = ":botte PRIVMSG " + channel.getName();
	msg += " :Undefined command.";
	msg += "\r\n";
	channel.sendMsgNoBot(msg, *this);
}
