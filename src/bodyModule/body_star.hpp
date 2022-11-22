/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2017 Immersive Adventure
 * Copyright (C) 2017-2020 AssociationSirius
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

#ifndef BODY_STAR_HPP_
#define BODY_STAR_HPP_

#include "bodyModule/body_sun.hpp"
#include "inGalaxyModule/starViewer.hpp"

class BodyStar : public Sun {
public:
    BodyStar(std::shared_ptr<Body> parent,
        const std::string& englishName,
        bool flagHalo,
        double radius,
        double oblateness,
        std::unique_ptr<BodyColor> myColor,
        float _sol_local_day,
        float albedo,
        std::unique_ptr<Orbit> orbit,
        bool close_orbit,
        ObjL* _currentObj,
        double orbit_bounding_radius,
        const BodyTexture &_bodyTexture);
    ~BodyStar();

    virtual bool drawGL(Projector* prj, const Navigator* nav, const Observer* observatory, const ToneReproductor* eye,
 	                    bool depthTest, bool drawHomePlanet, bool needClearDepthBuffer) override;
private:
    std::unique_ptr<StarViewer> starViewer;
};

#endif /* end of include guard: BODY_STAR_HPP_ */
