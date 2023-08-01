/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:39 by ajeanne           #+#    #+#             */
/*   Updated: 2023/08/01 16:18:53 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("default"), _logMsg("default"), _topic("default"), _password("default"), _secured(false), _owner(0), _maxUsr(0){
	return;	
}

Channel::Channel(std::string name, Client& owner) : _name(name), _logMsg("toto"), _topic("TURLUTUTU"), _password("toor"), _secured(false), _owner(owner.getSocket()), _maxUsr(0){

	addModo(owner);
	addUser(owner);
	
	_mode['i'] = false;
	_mode['t'] = false;
	_mode['k'] = false;
	_mode['o'] = false;
	_mode['l'] = false;
	_mode['b'] = false;

	std::stringstream ss;
	std::time_t now = std::time(0);
    ss << now;
	_creationTime = ss.str();
	_setat = ss.str();
}

Channel::~Channel(void)	{
	return;
}
