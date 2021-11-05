/*
* This source is the property of Immersive Adventure
* http://immersiveadventure.net/
*
* It has been developped by part of the LSS Team.
* For further informations, contact:
*
* albertpla@immersiveadventure.net
*
* This source code mustn't be copied or redistributed
* without the authorization of Immersive Adventure
* (c) 2017 - 2020 all rights reserved
*
*/
//! \file orbit_plot.hpp
//! \brief Draws a body's orbit
//! \author Julien LAFILLE
//! \date april 2018

#ifndef ORBIT_PLOT_HPP
#define ORBIT_PLOT_HPP

#include <vector>
#include <memory>

#include "tools/fader.hpp"
#include "tools/vecmath.hpp"
#include <vulkan/vulkan.h>

class Body;
class Projector;
class Navigator;
class VertexArray;
class VertexBuffer;
class Pipeline;
class PipelineLayout;

class OrbitPlot {
public:

	OrbitPlot()=delete;
	OrbitPlot(const OrbitPlot&) = delete;
	OrbitPlot(Body* body, int segments, int nbAdditionnalPoints = 0);

	virtual ~OrbitPlot();


	void setFlagOrbit(bool b) {
		orbit_fader = b;
	}

	virtual void drawOrbit(VkCommandBuffer &cmd, const Navigator * nav, const Projector* prj, const Mat4d &mat) = 0;
	virtual bool doDraw(const Navigator * nav, const Projector* prj, const Mat4d &mat) = 0;

	static void createSC_context();
	// static void deleteShader();

	void updateShader(double delta_time);
	LinearFader getOrbitFader() {
		return orbit_fader;
	}

	virtual void computeOrbit(double date);

	void init();

protected:

	void initDraw();

	Body * body;

	int ORBIT_POINTS;

	double delta_orbitJD;
	double last_orbitJD;
	bool orbit_cached;
	Vec3d * orbitPoint;

	LinearFader orbit_fader;

	std::unique_ptr<VertexBuffer> orbit;
	static Pipeline *pipelineOrbit2d, *pipelineOrbit3d;
	static PipelineLayout *layoutOrbit2d, *layoutOrbit3d;
	static std::unique_ptr<VertexArray> m_Orbit;
	const int nbAdditionnalPoints;
};

#endif
