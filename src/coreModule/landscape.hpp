/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2003 Fabien Chereau
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

#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <string>
#include <vector>
#include <memory>

#include "tools/vecmath.hpp"
#include "tools/auto_fader.hpp"
#include "tools/utility.hpp"

#include "tools/no_copy.hpp"
#include "tools/ScModule.hpp"

#include "EntityCore/Resource/SharedBuffer.hpp"

class s_texture;
class Navigator;
class Projector;
class VertexArray;
class VertexBuffer;
class Pipeline;
class PipelineLayout;
class Set;

class Fog;

// Class which manages the displaying of the Landscape
class Landscape: public NoCopy, public AModuleFader<ALinearFader> {

public:
	enum class LANDSCAPE_TYPE : char {
		FISHEYE,
		SPHERICAL
	};

	Landscape(float _radius = 2.);
	virtual ~Landscape();

	void setSkyBrightness(float b);

	//! Set the number of slices pour la construction des panoramas
	static void setSlices(int a) {
		a=a-a%5;  //on veut un nombre multiple de 5
		if (a>0)
			slices = a;
	}

	//! Set the number of stacks pour la construction des panoramas
	static void setStacks(int a) {
		a=a-a%5;  // on veut un nombre multiple de 5
		if (a>0)
			stacks = a;
	}

	//! Set whether fog is displayed
	void fogSetFlagShow(bool b);
	//! Get whether fog is displayed
	bool fogGetFlagShow() const;
	//! Get landscape name
	std::string getName() const {
		return name;
	}
	//! Get landscape author name
	std::string getAuthorName() const {
		return author;
	}
	//! Get landscape description
	std::string getDescription() const {
		return description;
	}

	virtual void setRotation(float rotation) {
		rotate_z = rotation;
	}

	virtual void draw(const Projector* prj, const Navigator* nav);

	static Landscape* createFromFile(const std::string& landscape_file, const std::string& section_name);
	static Landscape* createFromHash(stringHash_t & param);
	static std::string getFileContent(const std::string& landscape_file);
	static std::string getLandscapeNames(const std::string& landscape_file);
	static void createSC_context();
	static void destroySC_context();
protected:
	std::unique_ptr<Fog> fog;
	virtual void load(const std::string& file_name, const std::string& section_name) {};
	//! Load attributes common to all landscapes
	void loadCommon(const std::string& landscape_file, const std::string& section_name);
	virtual void setLanding(bool isLanding) {}
	float radius;
	float sky_brightness;
	bool valid_landscape;   // was a landscape loaded properly?

	std::string name;
	std::string author;
	std::string description;
	std::unique_ptr<s_texture> map_tex;
	std::unique_ptr<s_texture> map_tex_night;
	bool haveNightTex;
	bool m_limitedShade;				// non-night display
	float m_limitedShadeValue;			// indicates what percentage of light is kept for the night display
	unsigned int nbVertex;				// number of vertexes of the landscapes

	static int slices;
	static int stacks;
	static Pipeline *pipeline;
	static PipelineLayout *layout;
	static std::unique_ptr<VertexArray> vertexModel;
	std::unique_ptr<SharedBuffer<Mat4f>> uMV;
	struct frag {
		float sky_brightness;
		float fader;
	};
	std::unique_ptr<SharedBuffer<frag>> uFrag;
	std::unique_ptr<VertexBuffer> vertex;
	std::unique_ptr<Set> set;
	VkCommandBuffer cmds[6] {}; // normal, then night
	float rotate_z; // rotation around the z axis
};

class LandscapeFisheye : public Landscape {
public:
	LandscapeFisheye(float _radius = 1.);
	virtual ~LandscapeFisheye();
	virtual void load(const std::string& fileName, const std::string& section_name);
	void create(const std::string _name, const std::string _maptex, double _texturefov,
	            const float _rotate_z, const std::string _maptex_night, float limitedShade, const bool _mipmap);
private:
	void createFisheyeMesh(double radius, int slices, int stacks, double texture_fov, float *data);
	void initShader();
	float tex_fov;
};

class LandscapeSpherical : public Landscape {
public:
	LandscapeSpherical(float _radius = 1.);
	virtual ~LandscapeSpherical();
	virtual void load(const std::string& fileName, const std::string& section_name);
	void create(const std::string _name, const std::string _maptex, const float _base_altitude,
	            const float _top_altitude, const float _rotate_z, const std::string _maptex_night, float limitedShade, const bool _mipmap);
	virtual void draw(const Projector* prj, const Navigator* nav) override;
private:
	void createSphericalMesh(double radius, double one_minus_oblateness, int slices, int stacks,
	                         double bottom_altitude, double top_altitude, float * data);
	void initShader();
	virtual void setLanding(bool isLanding) override;
	float base_altitude, top_altitude;  // for partial sphere coverage
	ACustomLinearFader landingFader;
};

#endif // _LANDSCAPE_H_
