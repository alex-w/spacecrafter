/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2021 Jérémy Calvo
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
 * Spacecrafter is a free open project of of LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

#include <iostream>
#include "InSandBoxModule.hpp"
#include "eventModule/event.hpp"
#include "eventModule/event_recorder.hpp"
#include "eventModule/EventScreenFader.hpp"

#include "coreModule/skygrid_mgr.hpp"
#include "coreModule/skyline_mgr.hpp"
#include "coreModule/skydisplay_mgr.hpp"
#include "coreModule/milkyway.hpp"
#include "inGalaxyModule/dso3d.hpp"
#include "inGalaxyModule/cloudNavigator.hpp"
#include "inGalaxyModule/dsoNavigator.hpp"
#include "coreModule/starLines.hpp"
#include "ojmModule/ojm_mgr.hpp"
#include "inGalaxyModule/starNavigator.hpp"
#include "tools/context.hpp"
#include "tools/draw_helper.hpp"

InSandBoxModule::InSandBoxModule(std::shared_ptr<Core> _core, Observer *_observer) : core(_core), observer(_observer)
{
	module = MODULE::IN_SANDBOX;

    minAltToGoDown = 1.E10;
    maxAltToGoUp = 1.E14;
}

void InSandBoxModule::onEnter()
{
	core->setFlagIngalaxy(MODULE::IN_SANDBOX);
	std::cout << "->InSandBox" << std::endl;
	//set altitude in CoreExecutorInGalaxy when enter
	if (observer->getAltitude() < minAltToGoDown) {
		std::cout << "too low -> altitude = min" << std::endl;
		observer->setAltitude(maxAltToGoUp);
	} else
	if (observer->getAltitude() > maxAltToGoUp) {
		std::cout << "too high -> altitude = max" << std::endl;
		observer->setAltitude(minAltToGoDown);
	}
	else {
		std::cout << "InSandBox mode" << std::endl;
		// observer->setAltitude((minAltToGoDown+maxAltToGoUp/2.0));
	}
	// s_texture::willRead("MilkyWayRGBAVolume1024x1024x128.raw");
}

void InSandBoxModule::onExit()
{
	std::cout << "InSandBox->" << std::endl;
}

void InSandBoxModule::update(int delta_time)
{
		// Update the position of observation and time etc...
	observer->update(delta_time);
	core->timeMgr->update(delta_time);
	core->navigation->update(delta_time);

	// Position of sun and all the satellites (ie planets)
	core->ssystemFactory->computePositions(core->timeMgr->getJDay(), observer);

	core->ssystemFactory->updateAnchorManager();

	// Transform matrices between coordinates systems
	core->navigation->updateTransformMatrices(observer, core->timeMgr->getJDay());
	// Direction of vision
	core->navigation->updateVisionVector(delta_time, core->selected_object);
	// Field of view
	core->projection->updateAutoZoom(delta_time, core->FlagManualZoom);
	// Move the view direction and/or fov
	core->updateMove(delta_time);
	// Update faders
	core->update(delta_time);
	core->starLines->update(delta_time);
	core->milky_way->update(delta_time);
	core->dso3d->update(delta_time);

	// Give the updated standard projection matrices to the projector
	// NEEDED before atmosphere compute color
	core->projection->setModelViewMatrices( core->navigation->getEarthEquToEyeMat(),
	                                    core->navigation->getEarthEquToEyeMatFixed(),
	                                    core->navigation->getHelioToEyeMat(),
	                                    core->navigation->getLocalToEyeMat(),
	                                    core->navigation->getJ2000ToEyeMat(),
	                                    core->navigation->geTdomeMat(),
	                                    core->navigation->getDomeFixedMat());
	Event* event = new ScreenFaderInterludeEvent(
		ScreenFaderInterludeEvent::UP, maxAltToGoUp/2.0,maxAltToGoUp, observer->getAltitude());
	EventRecorder::getInstance()->queue(event);
}

void InSandBoxModule::draw(int delta_time)
{
	core->applyClippingPlanes(0.01, 2000.01);
	Context::instance->helper->beginDraw(PASS_BACKGROUND, *Context::instance->frame[Context::instance->frameIdx]);
	core->starNav->computePosition(core->navigation->getObserverHelioPos());
	core->cloudNav->computePosition(core->navigation->getObserverHelioPos(), core->projection);
	core->dsoNav->computePosition(core->navigation->getObserverHelioPos(), core->projection);

	//for VR360 drawing
	core->media->drawVR360(core->projection, core->navigation);

	core->milky_way->draw(core->tone_converter, core->projection, core->navigation, core->timeMgr->getJulian());

	if (core->selected_object && core->object_pointer_visibility) core->selected_object.drawPointer(delta_time, core->projection, core->navigation);
	//set mode
	//drawing lines without activating the depth buffer.
	//core->skyDisplayMgr->drawPerson(core->projection, core->navigation);
	//core->starLines->draw(core->navigation);

	// transparency.
	//core->dso3d->draw(observer->getAltitude(), core->projection, core->navigation);
	//core->ojmMgr->draw(core->projection, core->navigation, OjmMgr::STATE_POSITION::IN_GALAXY);
	//core->starNav->draw(core->navigation, core->projection, false);
	//core->dsoNav->draw(core->navigation, core->projection);
	//core->cloudNav->draw(core->navigation, core->projection);
	//core->postDraw();
}

bool InSandBoxModule::testValidAltitude(double altitude)
{
	if (altitude>maxAltToGoUp) {
		nextMode = upMode;
		Event* event = new ScreenFaderEvent(ScreenFaderEvent::FIX, 1.0);
		EventRecorder::getInstance()->queue(event);
		return true;
	}
	if (altitude<minAltToGoDown) {
		nextMode = (core->ssystemFactory->querySelectedAnchorName() == "Sun") ? downMode : downModeAlt;
		return true;
	}
	return false;
}
