/*
 * Spacecrafter astronomy simulation and visualization
 *
 * Copyright (C) 2014-2020 of the LSS Team & Association Sirius
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
 * Spacecrafter is a free open project of the LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */


#ifndef _MEDIA_HPP_
#define _MEDIA_HPP_

#include <map>
#include <string>
#include <memory>

#include "mediaModule/audio.hpp"
#include "mediaModule/image_mgr.hpp"
#include "mediaModule/text_mgr.hpp"
#include "mediaModule/video_player.hpp"
#include "mediaModule/vr360.hpp"
#include "mediaModule/viewport.hpp"
//#include "tools/app_settings.hpp"
#include "tools/no_copy.hpp"
#include "tools/context.hpp"
#include <vulkan/vulkan.h>

class Projector;
class Navigator;
class Subtitle;
class InitParser;

enum class AudioFunction : char {
	AF_MUSICLOAD,
	AF_MUSICPLAY,
	AF_MUSICPAUSE,
	AF_MUSICRESUME,
	AF_MUSICREWIND,
	AF_MUSICHALT,
	AF_MUSICSYNC,
	AF_MUSICDROP,
	AF_MUSICJUMP
};

enum class AudioVolume : char {
	AV_SETVOLUME,
	AV_INCREMENTVOLUME,
	AV_DECREMENTVOLUME
};

struct AudioParam {
	int value;
	std::string filename;
	bool loop;
	float secondJump;
};

struct VideoParam {
	std::string  name;
	std::string videoFileName;
	std::string audioFileName;
	std::string type;
	std::string position;
	IMG_PROJECT tmpProject;
};

//status of video playback
enum class V_TYPE : char { V_NONE, V_VIEWPORT, V_IMAGE, V_VR360, V_VRCUBE};
enum class V_STATE: char { V_NONE, V_PAUSE, V_PLAY };


class Media : public NoCopy {

public:
	Media(InitParser &conf);
	~Media();

	////////////////////////////////////////////////////////////////////////////
	//
	// other
	//
	////////////////////////////////////////////////////////////////////////////

	//! creation of structures for VR
	void initVR360();
	//! creation of Vulkan context
	void createSC_context();

	//! displays an image of the video player for the VR360
	void drawVR360(const Projector* prj, const Navigator* nav) {
		vr360->draw(prj, nav);
	}

	//! displays a video player image to the ViewPort
	void drawViewPort(double heading) {
		viewPort->draw(heading);
	}

	void faderUpdate(float delta_time) {
		viewPort->update(delta_time);
	}

	void disableFader() {
		viewPort->disableFader();
	}

	//! allows you to indicate to the shader the color to be erased
	//! \param color represents the 3 RGB components
	//! \param intensity represents -+ a delta of color difference
	void setKeyColor(const Vec3f &color, float intensity = 0.05) {
		viewPort->setKeyColor(color,intensity);
	}

	//! enables transparency when playing videos
	//! \param v represents the boolean .
	void setKeyColor(bool v) {
		viewPort->setTransparency(v);
	}

	void setProjector(const Projector* projection);

	////////////////////////////////////////////////////////////////////////////
	//
	//audio interface
	//
	////////////////////////////////////////////////////////////////////////////

	void audioFunction(const AudioFunction& audioFunction, const AudioParam& audioParam);

	void audioVolume(const AudioVolume& volumeOrder, float _value);

	void audioSetVolume(int _value) {
		audio->setVolume(_value);
	}

	void audioVolumeIncrement(int value=5) {
		audio->incrementVolume(value);
	}

	void audioVolumeDecrement(int value=5) {
		audio->decrementVolume(value);
	}

	void audioMusicLoad(const std::string &filename, bool loop);

	void audioMusicPlay() {
		audio->musicPlay();
	}

	void audioMusicMute() {
		if (!audioNoPause)
			audio->musicMute();
	}

	void audioMusicPause() {
		if (!audioNoPause)
			audio->musicPause();
	}

	void audioMusicResume() {
		audio->musicResume();
	}

	void audioMusicRewind() {
		audio->musicRewind();
	}

	void audioMusicHalt() {
		if (m_videoState.state != V_STATE::V_PLAY) {
			audio->musicHalt();
		}
	}

	void audioMusicSync() {
		audio->musicSync();
	}

	void audioMusicDrop() {
		audio->musicDrop();
	}

	void audioMusicJump(float deltaTime) {
		audio->musicJump(deltaTime);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	void audioUpdate(int delta_time) {
		audio->update(delta_time);
	}

	//! Allows you to set the behavior
	//! @param true: the music continues to play if the script is paused
	//! @param false: the music stops playing if the script is paused
	void audioSetMusicToPause(bool value) {
		audioNoPause = value;
	}
	////////////////////////////////////////////////////////////////////////////
	//
	//image interface
	//
	////////////////////////////////////////////////////////////////////////////
	int imageLoad(const std::string &filename, const  std::string &name, const std::string &coordinate, IMG_PROJECT project, bool mipmap) {
		return imageMgr->loadImage( filename,  name, coordinate, project, mipmap);
	}

	void imageDrop(const std::string &name) {
		return imageMgr->drop_image(name);
	}

	void imageDropAll() {
		return imageMgr->dropAllImages();
	}

	void imageDropAllNoPersistent() {
		return imageMgr->dropAllNoPersistent();
	}

	bool imageSet(const std::string &name) {
		return imageMgr->setImage(name);
	}

	void imageSetAlpha( float alpha, float duration) {
		imageMgr->setAlpha(alpha, duration);
	}

	void imageSetScale( float scale, float duration) {
		imageMgr->setScale(scale, duration);
	}

	void imageSetRotation( float rotation, float duration) {
		imageMgr->setRotation(rotation, duration);
	}

	void imageSetPersistent(bool value) {
		imageMgr->setPersistent(value);
	}

	void imageSetLocation(float xpos, bool deltax, float ypos, bool deltay, float duration, bool accelerate_x = false, bool decelerate_x = false, bool accelerate_y = false, bool decelerate_y = false) {
		imageMgr->setLocation(xpos, deltax, ypos, deltay, duration, accelerate_x, decelerate_x, accelerate_y, decelerate_y);
	}

	void imageSetRatio(float ratio, float duration) {
		imageMgr->setRatio(ratio, duration);
	}

	void imageUpdate(int delta_time) {
		imageMgr->update(delta_time);
	}

	void imageDraw(const Navigator * nav, const Projector * prj) {
		imageMgr->draw(nav, prj);
	}

	//! allows you to indicate to the shader the color to be erased
	//! \param color represents the 3 RGB components
	//! \param intensity represents -+ a delta of color difference
	void imageSetKeyColor(const Vec3f &color, float intensity = 0.05) {
		imageMgr->setKeyColor(color,intensity);
	}

	//! activates transparency when playing videos
	//! \param v represents the boolean .
	void imageSetKeyColor(bool v) {
		imageMgr->setTransparency(v);
	}

	////////////////////////////////////////////////////////////////////////////
	//
	//interface text
	//
	////////////////////////////////////////////////////////////////////////////
	void textAdd(const std::string& name, const TEXT_MGR_PARAM& textParam) {
		textMgr->add(name, textParam);
	}

	void textDel(std::string name) {
		textMgr->del(name);
	}

	void textClear() {
		textMgr->clear();
	}

	void textNameUpdate(std::string name, std::string text) {
		textMgr->textUpdate(name, text);
	}

	void textDisplay(std::string name , bool displ) {
		textMgr->textDisplay(name, displ);
	}

	void textFadingDuration(int a) {
		textMgr->setFadingDuration(a);
	}

	void textSetDefaultColor(const Vec3f& v) {
		textMgr->setColor(v);
	}

	void textDraw() {
		textMgr->draw(prj);
	}

	void setTextColor(const Vec3f &color) {
		textMgr->setColor(color);
	}

	void setTextFont(float font_size, const std::string& font_name) {
		textMgr->setFont(font_size,font_name);
	}

	void buildTextFont() {
		textMgr->buildFont();
	}

	void resetTextFont() {
		textMgr->resetFont();
	}

	void updateTextFont(double size, const std::string& fontName) {
		textMgr->updateFont(size, fontName);
	}

	////////////////////////////////////////////////////////////////////////////
	//
	//video interface
	//
	////////////////////////////////////////////////////////////////////////////
	VID_TYPE strToVideoType(const std::string& value);

	void setLoop(bool _loop) {
		loop = _loop;
	}

	bool getLoop() const {
		return loop;
	}

	bool getDualViewport() {
		return dualViewport;
	}

	void setDualViewport(bool _dualViewport) {
		dualViewport = _dualViewport;
		viewPort->displayFullScreen(!dualViewport);
		const int frameIdx = Context::instance->frameIdx;
		viewPort->build(frameIdx);
		viewPort->setTexture(player->getYUV_VideoTexture());
	}

	void playerUpdate() {
		player->update();
	}

	void playerPause() {
		player->pauseCurrentVideo();
		audio->musicPause();
	}

	bool playerPlay(const VID_TYPE &type, const std::string &videoname, const std::string &audioname, const std::string& _name, const std::string& _position, IMG_PROJECT tmpProject);

	void playerStop(bool newVideo);

	void playerRestart();

	void playerJump(float deltaTime);

	void playerInvertflow();

	bool playerIsVideoPlayed() const {
		return player->isVideoPlayed();
	}

	bool isVideoCacheFull() const {
		return player->isVideoCacheFull();
	}

	void playerRecordUpdate(VkCommandBuffer cmd) {
		player->recordUpdate(cmd);
	}
	void playerRecordUpdateDependency(VkCommandBuffer cmd) {
		player->recordUpdateDependency(cmd);
	}
private:
	bool playerPlay(const VID_TYPE &type, const std::string &filename, const std::string& _name, const std::string& _position, IMG_PROJECT tmpProject);

	std::unique_ptr<Audio> audio = nullptr;
	std::unique_ptr<ImageMgr> imageMgr = nullptr;
	std::unique_ptr<VideoPlayer> player = nullptr;
	std::unique_ptr<VR360> vr360 = nullptr;
	std::unique_ptr<ViewPort> viewPort = nullptr;
	std::unique_ptr<TextMgr> textMgr;				// manage all user text in dome
	std::unique_ptr<Subtitle> subtitle;
	const Projector *prj;

	std::string skyLanguage;
	bool mplayerEnable;
	bool audioNoPause=false;
	bool loop=false;
	bool dualViewport=false;

	std::string imageVideoName;
	bool audioNotInVideo;

	struct VideoState {
		V_TYPE type;
		V_STATE state;
	};

	VideoState m_videoState;
	std::map<std::string, VID_TYPE> strToVid;
};

#endif //MEDIA_HPP
