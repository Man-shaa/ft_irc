/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:39 by ajeanne           #+#    #+#             */
/*   Updated: 2023/07/02 16:45:28 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default"), _logMsg("default"), _topic("default"), _password("default"), _secured(false), _owner(0){
	return;	
}

Channel::Channel(std::string name, Client& owner) : _name(name), _logMsg("toto"), _topic("TURLUTUTU"), _password("toor"), _secured(false), _owner(owner.getSocket()){

	addModo(owner);
	addUser(owner);
	
	_mode['i'] = true;
	_mode['t'] = true;
	_mode['k'] = false;
	_mode['o'] = false;

	std::stringstream ss;
	std::time_t now = std::time(0);
    ss << now;
	_creationTime = ss.str();
	std::cout << _creationTime << std::endl;
}

Channel::~Channel(void)	{
	return;
}
