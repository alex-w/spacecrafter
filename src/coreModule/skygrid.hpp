/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2002 Fabien Chereau
 * Copyright (C) 2009 Digitalis Education Solutions, Inc.
 * Copyright (C) 2013 of the LSS team
 * Copyright (C) 2014 of the LSS Team & Association Sirius
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

#ifndef __SKYGRID_H__
#define __SKYGRID_H__

#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "tools/s_font.hpp"
#include "coreModule/projector.hpp"
#include "tools/fader.hpp"

#include "tools/ScModule.hpp"
#include "vulkanModule/Context.hpp"

//! Class which manages a grid to display in the sky

class VertexArray;
class Pipeline;
class PipelineLayout;
class Set;
class Uniform;
//class shaderProgram;

//TODO: intégrer qu'une version de font car la font est commune à toutes les grilles
//TODO: intégrer qu'une version du flag InternaNav qui est commun à toutes les grilles
class SkyGrid {
public:
	virtual ~SkyGrid();

	void draw(const Projector* prj) const;

	void setColor(const Vec3f& c) {
		color = c;
	}

	const Vec3f& getColor() {
		return color;
	}

	void update(int delta_time) {
		fader.update(delta_time);
	}

	void setFaderDuration(float duration) {
		fader.setDuration((int)(duration*1000.f));
	}

	void setFlagShow(bool b) {
		fader = b;
	}

	bool getFlagShow(void) const {
		return fader;
	}

	//! change FlagShow: inverse la valeur du flag
	void flipFlagShow() {
		fader=!fader;
	}

	void setInternalNav (bool a) {
		internalNav=a;
	}

	static void createShader(ThreadContext *_context);

	static void setFont(s_font* _font){
		font = _font;
	}

protected:
	// Create and precompute positions of a SkyGrid
	SkyGrid(unsigned int _nb_meridian = 24, unsigned int _nb_parallel = 17,
	        double _radius = 1., unsigned int _nb_alt_segment = 18, unsigned int _nb_azi_segment = 50);

	void createBuffer();
	//! Record draw command
	void recordDraw();

	enum SKY_GRID_TYPE {
		EQUATORIAL,
		ECLIPTIC,
		GALACTIC,
		ALTAZIMUTAL
	};
	SKY_GRID_TYPE gtype;
	bool (Projector::*proj_func)(const Vec3d&, Vec3d&) const;

	static unsigned int nbPointsToDraw;
	static ThreadContext *context;
	static VertexArray *m_dataGL;
	static Pipeline *pipeline;
	static PipelineLayout *layout;
	static Set *set;
	static int vUniformID0;
	static int vUniformID1;
	int commandIndex;
	std::unique_ptr<Uniform> uMat, uFrag;
	Mat4f *pMat;
	Vec3f *pColor;
	float *pFader;
	//static std::unique_ptr<shaderProgram> shaderSkyGrid;
	static s_font* font;
private:
	unsigned int nb_meridian;
	unsigned int nb_parallel;
	double radius;
	unsigned int nb_alt_segment;
	unsigned int nb_azi_segment;
	Vec3f color;
	Vec3f** alt_points;
	Vec3f** azi_points;
	bool internalNav;
	LinearFader fader;
};


class GridEquatorial: public SkyGrid {
public:
	GridEquatorial(unsigned int _nb_meridian = 24, unsigned int _nb_parallel = 17,
	               double _radius = 1., unsigned int _nb_alt_segment = 18, unsigned int _nb_azi_segment = 50)
		:SkyGrid(_nb_meridian, _nb_parallel, _radius, _nb_alt_segment, _nb_azi_segment) {
		gtype = EQUATORIAL;
		proj_func = &Projector::projectEarthEqu;
	}
};


class GridEcliptic: public SkyGrid {
public:
	GridEcliptic(unsigned int _nb_meridian = 24, unsigned int _nb_parallel = 17,
	             double _radius = 1., unsigned int _nb_alt_segment = 18, unsigned int _nb_azi_segment = 50)
		:SkyGrid(_nb_meridian, _nb_parallel, _radius, _nb_alt_segment, _nb_azi_segment) {
		gtype = ECLIPTIC;
		proj_func = &Projector::projectEarthEcliptic;
	}
};


class GridAltAzimutal: public SkyGrid {
public:
	GridAltAzimutal(unsigned int _nb_meridian = 24, unsigned int _nb_parallel = 17,
	                double _radius = 1., unsigned int _nb_alt_segment = 18, unsigned int _nb_azi_segment = 50)
		:SkyGrid(_nb_meridian, _nb_parallel, _radius, _nb_alt_segment, _nb_azi_segment) {
		gtype = ALTAZIMUTAL;
		proj_func = &Projector::projectLocal;
	}
};


class GridGalactic: public SkyGrid {
public:
	GridGalactic(unsigned int _nb_meridian = 24, unsigned int _nb_parallel = 17,
	             double _radius = 1., unsigned int _nb_alt_segment = 18, unsigned int _nb_azi_segment = 50)
		:SkyGrid(_nb_meridian, _nb_parallel, _radius, _nb_alt_segment, _nb_azi_segment) {
		gtype = GALACTIC;
		proj_func = &Projector::projectJ2000Galactic;
	}
};
#endif // __SKYGRID_H__
