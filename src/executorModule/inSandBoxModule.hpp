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

#ifndef _IN_SANDBOX_MODULE_
#define _IN_SANDBOX_MODULE_

#include "executorModule.hpp"
#include "coreModule/core.hpp"
#include "mediaModule/media.hpp"

class InSandBoxModule : public ExecutorModule {
public:

    InSandBoxModule(std::shared_ptr<Core> _core, Observer *_observer);
    ~InSandBoxModule() {};

    virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(int delta_time) override;
	virtual void draw(int delta_time) override;
    bool testValidAltitude(double altitude) override;

    void defineDownModeAlt(ExecutorModule *_downModeAlt) {
		downModeAlt = _downModeAlt;
	}
private:
    std::shared_ptr<Core> core;
    Observer *observer;
    ExecutorModule *downModeAlt = nullptr;
};

#endif
