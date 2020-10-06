/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2002 Fabien Chereau
 * Copyright (C) 2009 Digitalis Education Solutions, Inc.
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

#ifndef _OBJECT_BASE_H_
#define _OBJECT_BASE_H_


#include <vector>
#include <memory>
#include <iostream>

#include "tools/object_type.hpp"
#include "tools/vecmath.hpp"
//#include "renderGL/shader.hpp"
#include "renderGL/stateGL.hpp"
#include "vulkanModule/Context.hpp"

class Navigator;
class TimeMgr;
class Observer;
class Projector;
class s_texture;
//class shaderProgram;
class VertexArray;
class Pipeline;
class Uniform;

class ObjectBase;
void intrusivePtrAddRef(ObjectBase* p);
void intrusivePtrRelease(ObjectBase* p);

class ObjectBase {
public:
	virtual ~ObjectBase() {}
	virtual void retain() {}
	virtual void release() {}

	//! dessine le pointeur de l'objet sélectionné en fonction de son type.
	void drawPointer(int delta_time, const Projector* prj, const Navigator *nav);

	//! Write I18n information about the object in string.
	virtual std::string getInfoString(const Navigator * nav) const = 0;

	//! The returned string can typically be used for object labeling in the sky
	virtual std::string getShortInfoString(const Navigator *nav) const = 0;

	//! The returned nav string
	virtual std::string getShortInfoNavString(const Navigator *nav, const TimeMgr * timeMgr, const Observer* observatory) const = 0;

	//! Return object's type
	virtual OBJECT_TYPE getType() const = 0;

	//! Return object's name
	virtual std::string getEnglishName() const = 0;
	virtual std::string getNameI18n() const = 0;

	//! return Ra and Dec for a star
	virtual void getRaDeValue(const Navigator *nav,double *ra, double *de) const {};

	//! Get position in earth equatorial frame
	virtual Vec3d getEarthEquPos(const Navigator *nav) const = 0;

	//! observer centered J2000 coordinates
	virtual Vec3d getObsJ2000Pos(const Navigator *nav) const = 0;

	//! Return object's magnitude
	virtual float getMag(const Navigator *nav) const = 0;

	//! Get object main color, used to display infos
	virtual Vec3f getRGB() const {
		return Vec3f(1.,1.,1.);
	}

	virtual ObjectBaseP getBrightestStarInConstellation() const;

	//! Return the best FOV in degree to use for a close view of the object
	virtual double getCloseFov(const Navigator *nav) const {
		return 10.;
	}

	//! Return the best FOV in degree to use for a global view of the object satellite system (if there are satellites)
	virtual double getSatellitesFov(const Navigator *nav) const {
		return -1.;
	}
	virtual double getParentSatellitesFov(const Navigator *nav) const {
		return -1.;
	}

	//! fonction qui initialise les shaders permettant le dessin des pointeurs
	static void initTextures();

	//! fonction qui libère la mémoire des textures des pointeurs
	static void deleteTextures();

	virtual float getOnScreenSize(const Projector *prj, const Navigator *nav = NULL, bool orb_only = false) {
		return 0;
	}

	static void createShaderStarPointeur(ThreadContext *context);
	static void createShaderPointeur(ThreadContext *context);
	static void build();

protected:
	static int local_time;
	static s_texture * pointer_star;
	static s_texture * pointer_planet;
	static s_texture * pointer_nebula;
	std::vector<float> m_pos;
	std::vector<float> m_indice;
	Vec3f color;

	// GL
	static CommandMgr *cmdMgr, *cmdMgrTarget;
	static int commandIndexPointer, commandIndexStarPointer;
	static VertexArray *m_pointerGL, *m_starPointerGL;
	static Pipeline *m_pipelinePointer, *m_pipelineStarPointer;
	static PipelineLayout *m_layoutPointer, *m_layoutStarPointer;
	static Set *m_setPointer, *m_setStarPointer, *m_globalSet;
	static Uniform *m_uColor, *m_uGeom;
	static Vec3f *m_pColor;
	static OBJECT_TYPE lastType; // set default value which is different to every possible states
	static struct objBaseGeom {
		Mat4f matRotation;
		float radius;
	} *m_pGeom;
	//shader for the pointer
	//static std::unique_ptr<shaderProgram> m_shaderPointer, m_shaderStarPointer;
};

#endif
