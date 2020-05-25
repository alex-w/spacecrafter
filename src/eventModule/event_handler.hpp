/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2018 Elitit-40
 * Copyright (C) 2020 Elitit-40
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Spacecrafter is a free open project of the LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

/**
* \file event_handler.hpp
* \brief Register of event types and execute events
* \author Elitit
* \version 1
*/

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP


#include <iostream>
#include <map>
#include "event.hpp"

class EventRecorder;
class EventHandlerCanvas;
class Event;

class EventHandler{
public:
	EventHandler( EventRecorder* _eventManager);
	EventHandler(EventHandler const &) = delete;
	EventHandler& operator = (EventHandler const &) = delete;

	~EventHandler() {
	}

	void handleEvents();
    void handle(const Event* e);
	void add(EventHandlerCanvas *sE, Event::Event_Type et);
	void remove(Event::Event_Type et);

protected :
	EventRecorder* eventManager = nullptr;
	std::map<Event::Event_Type, EventHandlerCanvas *> handlerMap;
};

#endif
