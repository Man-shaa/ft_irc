/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:20:43 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/08/08 18:03:09 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

# include <iostream>
# include "Client.hpp"

class Bot : public Client
{
private:

public:

	Bot(void);
	Bot(int socketFd, std::string nickname);
	Bot(Bot const &copy);
	~Bot(void);

	
	void	sendHelp(Channel &channel);
	void	sendError(Channel &channel);
	void	sendHi(Channel &channel);
	void	sendJoke(Channel &channel);
};

#endif