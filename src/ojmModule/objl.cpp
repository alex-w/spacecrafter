#include "tools/call_system.hpp" //direxist
#include "tools/log.hpp"
#include <SDL2/SDL.h>

#include "ojmModule/objl.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

// Modèles disponibles
//
// https://space.frieger.com/asteroids/asteroids/


ObjL::ObjL()
{}

void ObjL::draw(VkCommandBuffer &cmd, const float screenSize)
{
	if (screenSize < 20) {
		this->low->draw(cmd);
	} else if (screenSize >180) {
		this->high->draw(cmd);
	} else {
		this->medium->draw(cmd);
	}
}

void ObjL::bind(VkCommandBuffer &cmd)
{
	this->high->bind(cmd);
}

void ObjL::bind(Pipeline &pipeline)
{
	this->high->bind(pipeline);
}

ObjL::~ObjL() {
}

bool ObjL::init(const std::string &repertory, const std::string &_name)
{
	std::string nameL = repertory+"/"+ _name +"_1L.ojm";
	std::string nameM = repertory+"/"+ _name +"_2M.ojm";
	std::string nameH = repertory+"/"+ _name +"_3H.ojm";

	//~ cout << nameL << endl << nameM << endl << nameH << endl;

	if ( (CallSystem::fileExist(nameL)) && (CallSystem::fileExist(nameM)) && (CallSystem::fileExist(nameH)) ) {
		this->high = std::make_unique<OjmL>(nameH);
		this->medium = std::make_unique<OjmL>(nameM);
		this->low = std::make_unique<OjmL>(nameL);

		if (this->low->getOk() && this->medium->getOk() && this->high->getOk())  {
			//~ printf("Les 3 ojm  %s sont ok\n", _name.c_str());
			cLog::get()->write("Loading object "+ _name);
			if (this->medium->getVertexCount() > 20000) {
				cLog::get()->write("Performance Issue : Too many vertices for '" + nameM + "' (Keep Below 20 000)", LOG_TYPE::L_WARNING);
			}
			if (this->low->getVertexCount() > 4000) {
				cLog::get()->write("Performance Issue : Too many vertices for '" + nameL + "' (Keep Below 4 000)", LOG_TYPE::L_WARNING);
			}
			return true;
		} else {
			//~ printf("Erreur de chargement d'un ojm %s\n", _name.c_str());
			cLog::get()->write("Error loading object "+ _name, LOG_TYPE::L_ERROR);
			return false;
		}
	} else {
		cLog::get()->write("Error loading file object " + _name, LOG_TYPE::L_ERROR);
		return false;
	}
}
