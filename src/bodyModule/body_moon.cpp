/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2017 Immersive Adventure
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


#include "bodyModule/body_moon.hpp"
#include "tools/shader.hpp"
#include "tools/stateGL.hpp"
#include "tools/file_path.hpp"

#include "bodyModule/axis.hpp"
#include "bodyModule/orbit_3d.hpp"
#include "bodyModule/axis.hpp"
#include "bodyModule/halo.hpp"
#include "bodyModule/hints.hpp"
#include "bodyModule/trail.hpp"
#include "bodyModule/axis.hpp"
#include "coreModule/projector.hpp"
#include "navModule/navigator.hpp"
#include "navModule/observer.hpp"


Moon::Moon(Body *parent,
           const std::string& englishName,
           bool flagHalo,
           double radius,
           double oblateness,
           BodyColor* _myColor,
           float _sol_local_day,
           float albedo,
           Orbit *orbit,
           bool close_orbit,
           ObjL* _currentObj,
           double orbit_bounding_radius,
		   BodyTexture* _bodyTexture):
	Body(parent,
	     englishName,
	     MOON,
	     flagHalo,
	     radius,
	     oblateness,
	     _myColor,
	     _sol_local_day,
	     albedo,
	     orbit,
	     close_orbit,
	     _currentObj,
	     orbit_bounding_radius,
		 _bodyTexture)
{
	if (_bodyTexture->tex_night != "") {
		tex_night = new s_texture(FilePath(_bodyTexture->tex_night,FilePath::TFP::TEXTURE).toString(), TEX_LOAD_TYPE_PNG_SOLID_REPEAT, 1);
	}
	//more adding could be placed here for the constructor of Moon
	selectShader();
	orbitPlot = new Orbit3D(this);
}

Moon::~Moon()
{
	if (orbitPlot) delete orbitPlot;
}

void Moon::selectShader()
{
	//bool useShaderMoonNormal = true;
	if (tex_heightmap!=nullptr) { //altimetry Shader
		myShader = SHADER_MOON_NORMAL_TES;
		myShaderProg = BodyShader::getShaderMoonNormalTes();
		return;
	}

	if (tex_night!=nullptr) { //altimetry Shader
		myShader = SHADER_MOON_NIGHT;
		myShaderProg = BodyShader::getShaderMoonNight();
		return;
	}

	if (tex_norm!=nullptr) { //bump Shader
		myShader = SHADER_MOON_BUMP;
		myShaderProg = BodyShader::getShaderMoonBump();
		return;
	}
	//if (useShaderMoonNormal) { // normal shaders
	myShader = SHADER_MOON_NORMAL;
	myShaderProg = BodyShader::getShaderMoonNormal();
	//}
}

void Moon::drawBody(const Projector* prj, const Navigator * nav, const Mat4d& mat, float screen_sz)
{
	StateGL::enable(GL_CULL_FACE);
	StateGL::disable(GL_BLEND);

	//glBindTexture(GL_TEXTURE_2D, tex_current->getID());

	myShaderProg->use();

	//load specific values for shader
	switch (myShader) {

		case SHADER_MOON_BUMP:
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_current->getID());

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_norm->getID());

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tex_eclipse_map->getID());
			break;

		case SHADER_MOON_NORMAL_TES:
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_current->getID());

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_norm->getID());

			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, tex_heightmap->getID());

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tex_eclipse_map->getID());
	
			break;

		case SHADER_MOON_NIGHT :
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_current->getID());

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_eclipse_map->getID());
			
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tex_night->getID());			
			break;

		case SHADER_MOON_NORMAL :
		default: //shader normal
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_current->getID());

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tex_eclipse_map->getID());
			break;
	}
	//paramétrage des matrices pour opengl4
	Mat4f proj = prj->getMatProjection().convert();
	Mat4f matrix=mat.convert();
	matrix = matrix * Mat4f::zrotation(C_PI/180*(axis_rotation + 90));

	Mat4f inv_matrix = matrix.inverse();
	myShaderProg->setUniform("ModelViewProjectionMatrix",proj*matrix);
	myShaderProg->setUniform("inverseModelViewProjectionMatrix",(proj*matrix).inverse());
	myShaderProg->setUniform("ModelViewMatrix",matrix);
	myShaderProg->setUniform("clipping_fov",prj->getClippingFov());
	myShaderProg->setUniform("planetScaledRadius",radius);

	//paramètres commun aux shaders sauf Sun
	myShaderProg->setUniform("planetRadius",initialRadius);
	myShaderProg->setUniform("planetOneMinusOblateness",one_minus_oblateness);
	myShaderProg->setUniform("ModelViewMatrix",matrix);
	myShaderProg->setUniform("NormalMatrix", inv_matrix.transpose());

	//int index=1;
	myShaderProg->setUniform("LightPosition",eye_sun);
	myShaderProg->setUniform("SunHalfAngle",sun_half_angle);

	Vec3f tmp= v3fNull;
	Vec3f tmp2(0.4, 0.12, 0.0);

	if (myShader == SHADER_MOON_BUMP || myShader == SHADER_MOON_NORMAL_TES) {
		if(getEnglishName() == "Moon")
			myShaderProg->setUniform("UmbraColor",tmp2);
		else
			myShaderProg->setUniform("UmbraColor",tmp);
	}

	Vec3d planet_helio = get_heliocentric_ecliptic_pos();
	Vec3d light = -planet_helio;
	light.normalize();

	// Parent may shadow this satellite
	tmp = nav->getHelioToEyeMat() * parent->get_heliocentric_ecliptic_pos();
	myShaderProg->setUniform("MoonPosition1",tmp);
	myShaderProg->setUniform("MoonRadius1",parent->getRadius());

	//tesselation
	if ( myShader == SHADER_MOON_NORMAL_TES) {
		myShaderProg->setUniform("TesParam", 
				Vec3i(bodyTesselation->getMinTesLevel(),bodyTesselation->getMaxTesLevel(), bodyTesselation->getMoonAltimetryFactor() ));
	}

	if ( myShader == SHADER_MOON_NORMAL_TES )
		currentObj->draw(screen_sz, GL_PATCHES);
	else
		currentObj->draw(screen_sz);

	myShaderProg->unuse();

	glActiveTexture(GL_TEXTURE0);
	StateGL::disable(GL_CULL_FACE);
}

void Moon::handleVisibilityFader(const Observer* observatory, const Projector* prj, const Navigator * nav)
{
	if (prj->getFov()>30) {
		// If not in the parent Body system OR one of the other sister moons do not draw
		if (observatory->isOnBody() && !observatory->isOnBody(parent) && parent != observatory->getHomeBody()->get_parent() && getEarthEquPos(nav).length() > 1) {
			// If further than 1 AU of object if flying
			visibilityFader = false; // orbits will fade in and out now
		}
		else {
			if ( !observatory->isOnBody() ) {
				visibilityFader = false;
			}
			else
				visibilityFader = true;
		}
	}
	else
		visibilityFader = true;
}
