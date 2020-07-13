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

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "coreModule/starLines.hpp"
#include "tools/utility.hpp"
#include "tools/log.hpp"
#include "coreModule/projector.hpp"
#include "navModule/navigator.hpp"
#include "tools/ia.hpp"
#include "tools/OpenGL.hpp"
#include "tools/shader.hpp"
#include "tools/Renderer.hpp"

StarLines::StarLines()
{
	createSC_context();
	lineColor =  Vec3f(1.0,1.0,0.0);
}

StarLines::~StarLines()
{
	linePos.clear();
}

void StarLines::createSC_context()
{
	shaderStarLines = std::make_unique<shaderProgram>();
	shaderStarLines -> init("starLines.vert","starLines.geom", "starLines.frag");
	shaderStarLines->setUniformLocation({"Mat", "Color", "Fader"});
	
	m_dataGL = std::make_unique<VertexArray>();
	m_dataGL->registerVertexBuffer(BufferType::POS3D, BufferAccess::DYNAMIC);
}


bool StarLines::loadCat(const std::string& fileName, bool useBinary) noexcept
{
	if (useBinary)
		return this->loadHipBinCat(fileName);
	else
		return this->loadHipCat(fileName);
}

bool StarLines::saveCat(const std::string& fileName, bool useBinary) noexcept
{
	if (useBinary)
		return this->saveHipBinCat(fileName);
	else
		return this->saveHipCat(fileName);
}


bool StarLines::loadHipCat(const std::string& fileName) noexcept
{
	std::cout << "StarLines::loadHipCatalogue " << fileName << std::endl;
	std::ifstream fileIn(fileName);

	if (!fileIn.is_open()) {
		cLog::get()->write("StarLines error opening "+fileName, LOG_TYPE::L_ERROR);
		return false;
	}

	std::string record;
	int hip;
	float x,y,z;
	HIPpos tmp;
	unsigned int numberRead=0;

	while (!fileIn.eof() && std::getline(fileIn, record)) {

		if (record.size()!=0 && record[0]=='#')
			continue;

		std::istringstream istr(record);
		if (!(istr >> hip >> x >> y >> z)) {
			cLog::get()->write("StarLines error parsing HIP_data "+record, LOG_TYPE::L_ERROR);
			std::cout << "StarLines stars readed " << numberRead << std::endl;
			return false;
		}
		tmp.first = hip;
		tmp.second = Vec3f(-x,y,z);
		HIP_data.push_back(tmp);
		numberRead++;
	}
	fileIn.close();
	cLog::get()->write("StarLines cat "+fileName, LOG_TYPE::L_DEBUG);
	cLog::get()->write("StarLines stars readed "+ Utility::longToString(numberRead), LOG_TYPE::L_DEBUG);
	std::cout << "StarLines stars readed " << numberRead << std::endl;
	return true;
}


void StarLines::loadHipStar(int name, Vec3f position ) noexcept
{
	HIPpos tmp;
	tmp.first = name;
	tmp.second = position;
	HIP_data.push_back(tmp);
}

bool StarLines::saveHipCat(const std::string& fileName) noexcept
{
	std::cout << "StarLines::saveHipCatalogue " << fileName << std::endl;
	std::ofstream fileOut(fileName);

	if (!fileOut.is_open()) {
		cLog::get()->write("StarLines error opening "+fileName, LOG_TYPE::L_ERROR);
		return false;
	}
	fileOut << "# Created by SC StarLines::saveHipCatalogue " << std::endl;
	for( auto it = HIP_data.begin(); it!= HIP_data.end(); it++) {
		fileOut << (*it).first << " " << -(*it).second[0] << " " << (*it).second[1]  << " " << (*it).second[2] << std::endl;
	}
	fileOut.close();
	return true;
}

bool StarLines::saveHipBinCat(const std::string& fileName) noexcept
{
	std::cout << "StarLines::saveHipBinCatalogue " << fileName << std::endl;
	std::ofstream fileOut(fileName);

	if (!fileOut.is_open()) {
		cLog::get()->write("StarLines error opening "+fileName, LOG_TYPE::L_ERROR);
		return false;
	}

	float x,y,z;
	int nbr;

	for( auto it = HIP_data.begin(); it!= HIP_data.end(); it++) {
		nbr = (*it).first;
		x= -(*it).second[0];
		y= (*it).second[1];
		z= (*it).second[2];
	 	fileOut.write((char *)&nbr, sizeof(nbr));
	 	fileOut.write((char *)&x, sizeof(x));
	 	fileOut.write((char *)&y, sizeof(y));
	 	fileOut.write((char *)&z, sizeof(z));
	}
	fileOut.close();
	return true;
}

bool StarLines::loadHipBinCat(const std::string& fileName) noexcept
{
	std::cout << "StarLines::loadHipBinCatalogue " << fileName << std::endl;
	std::ifstream fileIn(fileName, std::ios::binary|std::ios::in );

	if (!fileIn.is_open()) {
		cLog::get()->write("StarLines error opening binary "+fileName, LOG_TYPE::L_ERROR);
		return false;
	}

	std::string record;
	int hip;
	float x,y,z;
	HIPpos tmp;
	char Ver[3];
	unsigned int numberRead = 0;
	//lecture version
	fileIn.read((char *)&Ver,sizeof(Ver));
	//~ printf("%c %c %c\n", Ver[0], Ver[1], Ver[2]);

	//lecture des etoiles
	while (!fileIn.eof()) {

		fileIn.read((char *)&hip,sizeof(hip));
		fileIn.read((char *)&x,sizeof(x));
		fileIn.read((char *)&y,sizeof(y));
		fileIn.read((char *)&z,sizeof(z));

		tmp.first = hip;
		tmp.second = Vec3f(-x,y,z);
		HIP_data.push_back(tmp);
		numberRead++;
	}
	fileIn.close();
	cLog::get()->write("StarLines bin cat "+fileName, LOG_TYPE::L_DEBUG);
	cLog::get()->write("StarLines stars readed : "+ Utility::longToString(numberRead), LOG_TYPE::L_DEBUG);
	std::cout << "StarLines stars readed : " << numberRead << std::endl;
	return true;
}


bool StarLines::loadData(const std::string& fileName) noexcept
{
	std::ifstream fileIn(fileName);

	if (!fileIn.is_open()) {
		cLog::get()->write("StarLines error opening Data "+fileName, LOG_TYPE::L_ERROR);
		return false;
	}

	std::string record;
	linePos.clear();

	while (!fileIn.eof() && std::getline(fileIn, record)) {

		if (record.size()!=0 && record[0]=='#')
			continue;

		loadStringData(record);
	}
	cLog::get()->write("StarLines read Data "+fileName, LOG_TYPE::L_INFO);
	return true;
}


void StarLines::loadStringData(const std::string& record) noexcept
{
	unsigned int HIP1;
	unsigned int HIP2;
	Vec3f VNull(0.0,0.0,0.0);
	std::string abbreviation;
	unsigned int nb_segments=0;

	std::istringstream istr(record);
	if (!(istr >> abbreviation >> nb_segments)) {
		cLog::get()->write("StarLines error parsing line "+record, LOG_TYPE::L_ERROR);
		//printf("StarLines error parsing\n");
		return;
	}

	for (unsigned int i=0; i<nb_segments; ++i) {
		HIP1 = 0;
		HIP2 = 0;
		istr >> HIP1 >> HIP2;

		if (HIP1==0 || HIP2==0) {
			cLog::get()->write("StarLines error parsing line ", LOG_TYPE::L_ERROR);
			//printf("StarLines error parsing line\n");
			continue;
		}

		Vec3f tmp1 = searchInHip(HIP1);
		Vec3f tmp2 = searchInHip(HIP2);
		if (tmp1==VNull || tmp2 ==VNull) {
			if (tmp1==VNull) {
				//printf("StarLines error parsing HIP %i not found\n", HIP1);
				cLog::get()->write("StarLines error parsing not found HIP " + Utility::intToString(HIP1), LOG_TYPE::L_ERROR);
			}
			if (tmp2==VNull) {
				//printf("StarLines error parsing HIP %i not found\n", HIP2);
				cLog::get()->write("StarLines error parsing not found HIP " + Utility::intToString(HIP2), LOG_TYPE::L_ERROR);
			}
			continue;
		} else {
			// SEGMENT THE LINES
			int nblines=10;
			for(int j=0; j<nblines ; j++) {
				linePos.push_back(tmp1[0]*(nblines-j)/nblines+tmp2[0]*j/nblines);
				linePos.push_back(tmp1[1]*(nblines-j)/nblines+tmp2[1]*j/nblines);
				linePos.push_back(tmp1[2]*(nblines-j)/nblines+tmp2[2]*j/nblines);
				linePos.push_back(tmp1[0]*(nblines-(j+1))/nblines+tmp2[0]*(j+1)/nblines);
				linePos.push_back(tmp1[1]*(nblines-(j+1))/nblines+tmp2[1]*(j+1)/nblines);
				linePos.push_back(tmp1[2]*(nblines-(j+1))/nblines+tmp2[2]*(j+1)/nblines);
			}
		}
	}
	m_dataGL->fillVertexBuffer(BufferType::POS3D, linePos);
}


void StarLines::drop()
{
	linePos.clear();
}

Vec3f StarLines::searchInHip(int HIP)
{
	for (std::vector<HIPpos>::iterator it = HIP_data.begin() ; it != HIP_data.end(); ++it) {
		if ((*it).first == HIP) {
			return (*it).second;
		}
	}
	return v3fNull;
}

//version 3D in GALAXY mode
void StarLines::draw(const Navigator * nav) noexcept
{
	//commun aux deux fonctions
	if (linePos.size()<2)
		return;
	if (!showFader.getInterstate() ) return;

	//paramétrage des matrices pour opengl4
	Mat4f matrix=nav->getHelioToEyeMat().convert();
	matrix=matrix*Mat4f::xrotation(-M_PI_2-23.4392803055555555556*M_PI/180);

	this->drawGL(matrix);
}

//version 2D, in SOLAR_SYSTEM MODE
void StarLines::draw(const Projector* prj) noexcept
{
	//commun aux deux fonctions
	if (linePos.size()<2)
		return;
	if (!showFader.getInterstate() ) return;

	//paramétrage des matrices pour opengl4
	Mat4f matrix= prj-> getMatJ2000ToEye()*Mat4f::xrotation(-M_PI_2);

	this->drawGL(matrix);
}


//version 3D
void StarLines::drawGL(Mat4f & matrix)  noexcept
{
	StateGL::enable(GL_BLEND);
	StateGL::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Normal transparency mode

	shaderStarLines->use();
	shaderStarLines->setUniform("Mat",matrix);
	shaderStarLines->setUniform("Color",lineColor);
	shaderStarLines->setUniform("Fader", showFader.getInterstate() );

	// m_dataGL->bind();
	// glDrawArrays(GL_LINES,0,linePos.size()/3);
	// m_dataGL->unBind();
	// shaderStarLines->unuse();
	Renderer::drawArrays(shaderStarLines.get(), m_dataGL.get(), GL_LINES,0,linePos.size()/3);
}
