#include "interfaceModule/app_command_init.hpp"
#include <vector>
#include "tools/log.hpp"

AppCommandInit::AppCommandInit()
{
	setObsoleteToken();
}

AppCommandInit::~AppCommandInit()
{}


void AppCommandInit::setObsoleteToken()
{
	obsoletList.push_back("constellation_isolate_selected");
	obsoletList.push_back("point_star");
	obsoletList.push_back("movetocity");
	obsoletList.push_back("landscape_sets_location");
	obsoletList.push_back("external_mplayer");
}

bool AppCommandInit::isObsoleteToken(const std::string &source)
{
	for(auto it = obsoletList.begin(); it!=obsoletList.end(); it++ ) {
		if (*it== source) {
			cLog::get()->write(source + " is no longer used in software",LOG_TYPE::L_DEBUG, LOG_FILE::SCRIPT );
			return true;
		}
	}
	return false;
}


void AppCommandInit::initialiseCommandsName(std::map<const std::string, SC_COMMAND> &m_commands, std::map<SC_COMMAND, const std::string> &m_commandsToString)
{
	m_commands[ACP_CN_ADD] = SC_COMMAND::SC_ADD;
	m_commands[ACP_CN_AUDIO] = SC_COMMAND::SC_AUDIO;
	m_commands[ACP_CN_BODY_TRACE] = SC_COMMAND::SC_BODY_TRACE;
	m_commands[ACP_CN_BODY] = SC_COMMAND::SC_BODY;
	m_commands[ACP_CN_CAMERA] = SC_COMMAND::SC_CAMERA;
	m_commands[ACP_CN_FLYTO] = SC_COMMAND::SC_CAMERA; //alias de camera
	m_commands[ACP_CN_CLEAR] = SC_COMMAND::SC_CLEAR;
	m_commands[ACP_CN_COLOR] = SC_COMMAND::SC_COLOR;
	m_commands[ACP_CN_CONFIGURATION] = SC_COMMAND::SC_CONFIGURATION;
	m_commands[ACP_CN_CONSTELLATION] = SC_COMMAND::SC_CONSTELLATION;
	m_commands[ACP_CN_DATE] = SC_COMMAND::SC_DATE;
	m_commands[ACP_CN_DEFINE] = SC_COMMAND::SC_DEFINE;
	m_commands[ACP_CN_DESELECT] = SC_COMMAND::SC_DESELECT;
	m_commands[ACP_CN_DOMEMASTERS] = SC_COMMAND::SC_DOMEMASTERS;
	m_commands[ACP_CN_DSO] = SC_COMMAND::SC_DSO;
	m_commands[ACP_CN_EXTERNAL_VIEWER] = SC_COMMAND::SC_EXTERNASC_VIEWER;
	m_commands[ACP_CN_FONT] = SC_COMMAND::SC_FONT;
	m_commands[ACP_CN_HEADING] = SC_COMMAND::SC_HEADING;
	m_commands[ACP_CN_FLAG] = SC_COMMAND::SC_FLAG;
	m_commands[ACP_CN_GET] = SC_COMMAND::SC_GET;
	m_commands[ACP_CN_ILLUMINATE] = SC_COMMAND::SC_ILLUMINATE;
	m_commands[ACP_CN_IMAGE] = SC_COMMAND::SC_IMAGE;
	m_commands[ACP_CN_LANDSCAPE] = SC_COMMAND::SC_LANDSCAPE;
	m_commands[ACP_CN_SCREEN_FADER] = SC_COMMAND::SC_SCREEN_FADER;
	m_commands[ACP_CN_LOOK_AT] = SC_COMMAND::SC_LOOK;
	m_commands[ACP_CN_MEDIA] = SC_COMMAND::SC_MEDIA;
	m_commands[ACP_CN_METEORS] = SC_COMMAND::SC_METEORS;
	m_commands[ACP_CN_MOVETO] = SC_COMMAND::SC_MOVETO;
	m_commands[ACP_CN_MULTIPLY] = SC_COMMAND::SC_MULTIPLY;
	m_commands[ACP_CN_PERSONAL] = SC_COMMAND::SC_PERSONAL;
	m_commands[ACP_CN_PERSONEQ] = SC_COMMAND::SC_PERSONEQ;
	m_commands[ACP_CN_PLANET_SCALE] = SC_COMMAND::SC_PLANET_SCALE;
	m_commands[ACP_CN_POSITION] = SC_COMMAND::SC_POSITION;
	m_commands[ACP_CN_PRINT] = SC_COMMAND::SC_PRINT;
	m_commands[ACP_CN_RANDOM] = SC_COMMAND::SC_RANDOM;
	m_commands[ACP_CN_SCRIPT] = SC_COMMAND::SC_SCRIPT;
	m_commands[ACP_CN_SEARCH] = SC_COMMAND::SC_SEARCH;
	m_commands[ACP_CN_SELECT] = SC_COMMAND::SC_SELECT;
	m_commands[ACP_CN_SET] = SC_COMMAND::SC_SET;
	m_commands[ACP_CN_SHUTDOWN] = SC_COMMAND::SC_SHUTDOWN;
	m_commands[ACP_CN_SKY_CULTURE] = SC_COMMAND::SC_SKY_CULTURE;
	m_commands[ACP_CN_STAR_LINES] = SC_COMMAND::SC_STAR_LINES;
	m_commands[ACP_CN_STRUCT] = SC_COMMAND::SC_STRUCT;
	m_commands[ACP_CN_SUB] = SC_COMMAND::SC_SUB;
	m_commands[ACP_CN_SUNTRACE] = SC_COMMAND::SC_SUNTRACE;
	m_commands[ACP_CN_TEXT] = SC_COMMAND::SC_TEXT;
	m_commands[ACP_CN_TIMERATE] = SC_COMMAND::SC_TIMERATE;
	m_commands[ACP_CN_WAIT] = SC_COMMAND::SC_WAIT;
	m_commands[ACP_CN_ZOOM] = SC_COMMAND::SC_ZOOMR;

	for (auto it = m_commands.begin(); it != m_commands.end(); ++it) {
        m_commandsToString.emplace(it->second, it->first);
    }

	//make a copy to futur exploitation
	for (const auto& i : m_commands) {
		commandList.push_back(i.first);
	}

}

void AppCommandInit::initialiseFlagsName(std::map<const std::string, FLAG_NAMES> &m_flags, std::map<FLAG_NAMES,const std::string> &m_flagsToString)
{
	m_flags[ACP_FN_ANTIALIAS_LINES] = FLAG_NAMES::FN_ANTIALIAS_LINES;
	m_flags[ACP_FN_CONSTELLATION_DRAWING] = FLAG_NAMES::FN_CONSTELLATION_DRAWING;
	m_flags[ACP_FN_CONSTELLATION_NAMES] = FLAG_NAMES::FN_CONSTELLATION_NAMES;
	m_flags[ACP_FN_CONSTELLATION_ART] = FLAG_NAMES::FN_CONSTELLATION_ART;
	m_flags[ACP_FN_CONSTELLATION_BOUNDARIES] = FLAG_NAMES::FN_CONSTELLATION_BOUNDARIES;
	m_flags[ACP_FN_CONSTELLATION_PICK] = FLAG_NAMES::FN_CONSTELLATION_PICK;
	m_flags[ACP_FN_STAR_TWINKLE] = FLAG_NAMES::FN_STAR_TWINKLE;
	m_flags[ACP_FN_NAVIGATION] = FLAG_NAMES::FN_NAVIGATION;
	m_flags[ACP_FN_SHOW_TUI_DATETIME] = FLAG_NAMES::FN_SHOW_TUI_DATETIME;
	m_flags[ACP_FN_SHOW_TUI_SHORT_OBJ_INFO] = FLAG_NAMES::FN_SHOW_TUI_SHORT_OBJ_INFO;
	m_flags[ACP_FN_MANUAL_ZOOM] = FLAG_NAMES::FN_MANUAL_ZOOM;
	m_flags[ACP_FN_LIGHT_TRAVEL_TIME] = FLAG_NAMES::FN_LIGHT_TRAVEL_TIME;
	m_flags[ACP_FN_FOG] = FLAG_NAMES::FN_FOG;
	m_flags[ACP_FN_ATMOSPHERE] = FLAG_NAMES::FN_ATMOSPHERE;
	m_flags[ACP_FN_AZIMUTHAL_GRID] = FLAG_NAMES::FN_AZIMUTHAL_GRID;
	m_flags[ACP_FN_EQUATORIAL_GRID] = FLAG_NAMES::FN_EQUATORIAL_GRID;
	m_flags[ACP_FN_ECLIPTIC_GRID] = FLAG_NAMES::FN_ECLIPTIC_GRID;
	m_flags[ACP_FN_GALACTIC_GRID] = FLAG_NAMES::FN_GALACTIC_GRID;
	m_flags[ACP_FN_EQUATOR_LINE] = FLAG_NAMES::FN_EQUATOR_LINE;
	m_flags[ACP_FN_GALACTIC_LINE] = FLAG_NAMES::FN_GALACTIC_LINE;
	m_flags[ACP_FN_ECLIPTIC_LINE] = FLAG_NAMES::FN_ECLIPTIC_LINE;
	m_flags[ACP_FN_PRECESSION_CIRCLE] = FLAG_NAMES::FN_PRECESSION_CIRCLE;
	m_flags[ACP_FN_CIRCUMPOLAR_CIRCLE] = FLAG_NAMES::FN_CIRCUMPOLAR_CIRCLE;
	m_flags[ACP_FN_TROPIC_LINES] = FLAG_NAMES::FN_TROPIC_LINES;
	m_flags[ACP_FN_MERIDIAN_LINE] = FLAG_NAMES::FN_MERIDIAN_LINE;
	m_flags[ACP_FN_ZENITH_LINE] = FLAG_NAMES::FN_ZENITH_LINE;
	m_flags[ACP_FN_POLAR_CIRCLE] = FLAG_NAMES::FN_POLAR_CIRCLE;
	m_flags[ACP_FN_POLAR_POINT] = FLAG_NAMES::FN_POLAR_POINT;
	m_flags[ACP_FN_ECLIPTIC_CENTER] = FLAG_NAMES::FN_ECLIPTIC_CENTER;
	m_flags[ACP_FN_GALACTIC_POLE] = FLAG_NAMES::FN_GALACTIC_POLE;
	m_flags[ACP_FN_GALACTIC_CENTER] = FLAG_NAMES::FN_GALACTIC_CENTER;
	m_flags[ACP_FN_VERNAL_POINTS] = FLAG_NAMES::FN_VERNAL_POINTS;
	m_flags[ACP_FN_ANALEMMA_LINE] = FLAG_NAMES::FN_ANALEMMA_LINE;
	m_flags[ACP_FN_ANALEMMA] = FLAG_NAMES::FN_ANALEMMA;
	m_flags[ACP_FN_ARIES_LINE] = FLAG_NAMES::FN_ARIES_LINE;
	m_flags[ACP_FN_ZODIAC] = FLAG_NAMES::FN_ZODIAC;
	m_flags[ACP_FN_PERSONAL] = FLAG_NAMES::FN_PERSONAL;
	m_flags[ACP_FN_PERSONEQ] = FLAG_NAMES::FN_PERSONEQ;
	m_flags[ACP_FN_NAUTICAL_ALT] = FLAG_NAMES::FN_NAUTICAL;
	m_flags[ACP_FN_NAUTICAL_RA] = FLAG_NAMES::FN_NAUTICEQ;
	m_flags[ACP_FN_OBJECT_COORDINATES] = FLAG_NAMES::FN_OBJCOORD;
	m_flags[ACP_FN_MOUSE_COORDINATES] = FLAG_NAMES::FN_MOUSECOORD;
	m_flags[ACP_FN_ANGULAR_DISTANCE] = FLAG_NAMES::FN_ANG_DIST;
	m_flags[ACP_FN_LOXODROMY] = FLAG_NAMES::FN_LOXODROMY;
	m_flags[ACP_FN_ORTHODROMY] = FLAG_NAMES::FN_ORTHODROMY;
	m_flags[ACP_FN_GREENWICH_LINE] = FLAG_NAMES::FN_GREENWICH_LINE;
	m_flags[ACP_FN_VERTICAL_LINE] = FLAG_NAMES::FN_VERTICAL_LINE;
	m_flags[ACP_FN_CARDINAL_POINTS] = FLAG_NAMES::FN_CARDINAL_POINTS;
	m_flags[ACP_FN_CLOUDS] = FLAG_NAMES::FN_CLOUDS;
	m_flags[ACP_FN_MOON_SCALED] = FLAG_NAMES::FN_MOON_SCALED;
	m_flags[ACP_FN_SUN_SCALED] = FLAG_NAMES::FN_SUN_SCALED;
	m_flags[ACP_FN_LANDSCAPE] = FLAG_NAMES::FN_LANDSCAPE;
	m_flags[ACP_FN_STARS] = FLAG_NAMES::FN_STARS;
	m_flags[ACP_FN_STAR_NAMES] = FLAG_NAMES::FN_STAR_NAMES;
	m_flags[ACP_FN_STAR_PICK] = FLAG_NAMES::FN_STAR_PICK;
	m_flags[ACP_FN_ATMOSPHERIC_REFRACTION] = FLAG_NAMES::FN_ATMOSPHERIC_REFRACTION;
	m_flags[ACP_FN_PLANETS] = FLAG_NAMES::FN_PLANETS;
	m_flags[ACP_FN_PLANET_NAMES] = FLAG_NAMES::FN_PLANET_NAMES;
	m_flags[ACP_FN_PLANET_ORBITS] = FLAG_NAMES::FN_PLANET_ORBITS;
	m_flags[ACP_FN_ORBITS] = FLAG_NAMES::FN_ORBITS;
	m_flags[ACP_FN_PLANETS_ORBITS] = FLAG_NAMES::FN_PLANETS_ORBITS;
	m_flags[ACP_FN_PLANETS_AXIS] = FLAG_NAMES::FN_PLANETS_AXIS;
	m_flags[ACP_FN_SATELLITES_ORBITS] = FLAG_NAMES::FN_SATELLITES_ORBITS;
	m_flags[ACP_FN_NEBULAE] = FLAG_NAMES::FN_NEBULAE;
	m_flags[ACP_FN_NEBULA_NAMES] = FLAG_NAMES::FN_NEBULA_NAMES;
	m_flags[ACP_FN_NEBULA_HINTS] = FLAG_NAMES::FN_NEBULA_HINTS;
	m_flags[ACP_FN_MILKY_WAY] = FLAG_NAMES::FN_MILKY_WAY;
	m_flags[ACP_FN_BRIGHT_NEBULAE] = FLAG_NAMES::FN_BRIGHT_NEBULAE;
	m_flags[ACP_FN_OBJECT_TRAILS] = FLAG_NAMES::FN_OBJECT_TRAILS;
	m_flags[ACP_FN_TRACK_OBJECT] = FLAG_NAMES::FN_TRACK_OBJECT;
	m_flags[ACP_FN_SCRIPT_GUI_DEBUG] = FLAG_NAMES::FN_SCRIPT_GUI_DEBUG;
	m_flags[ACP_FN_LOCK_SKY_POSITION] = FLAG_NAMES::FN_LOCK_SKY_POSITION;
	m_flags[ACP_FN_BODY_TRACE] = FLAG_NAMES::FN_BODY_TRACE;
	m_flags[ACP_FN_SHOW_LATLON] = FLAG_NAMES::FN_SHOW_LATLON;
	m_flags[ACP_FN_COLOR_INVERSE] = FLAG_NAMES::FN_COLOR_INVERSE;
	m_flags[ACP_FN_OORT] = FLAG_NAMES::FN_OORT;
	m_flags[ACP_FN_STARS_TRACE] = FLAG_NAMES::FN_STARS_TRACE;
	m_flags[ACP_FN_STAR_LINES] = FLAG_NAMES::FN_STAR_LINES;
	m_flags[ACP_FN_DSO_PICTOGRAMS] = FLAG_NAMES::FN_DSO_PICTOGRAMS;
	m_flags[ACP_FN_ZODIACAL_LIGHT] = FLAG_NAMES::FN_ZODIAC_LIGHT;
	m_flags[ACP_FN_TULLY] = FLAG_NAMES::FN_TULLY;
	m_flags[ACP_FN_TULLY_COLOR_MODE] = FLAG_NAMES::FN_TULLY_COLOR_MODE;
	m_flags[ACP_FN_SATELLITES] = FLAG_NAMES::FN_SATELLITES;

	for (auto it = m_flags.begin(); it != m_flags.end(); ++it) {
        m_flagsToString.emplace(it->second, it->first);
    }

	//make a copy to futur exploitation
	for (const auto& i : m_flags) {
		flagList.push_back(i.first);
	}
}

void AppCommandInit::initialiseColorCommand(std::map<const std::string, COLORCOMMAND_NAMES> &m_color, std::map<COLORCOMMAND_NAMES, const std::string> &m_colorToString)
{
	m_color[ACP_CC_CONSTELLATION_LINES] = COLORCOMMAND_NAMES::CC_CONSTELLATION_LINES;
	m_color[ACP_CC_CONSTELLATION_NAMES] = COLORCOMMAND_NAMES::CC_CONSTELLATION_NAMES;
	m_color[ACP_CC_CONSTELLATION_ART] = COLORCOMMAND_NAMES::CC_CONSTELLATION_ART;
	m_color[ACP_CC_CONSTELLATION_BOUNDARIES] = COLORCOMMAND_NAMES::CC_CONSTELLATION_BOUNDARIES;
	m_color[ACP_CC_CARDINAL_POINTS] = COLORCOMMAND_NAMES::CC_CARDINAL_POINTS;
	m_color[ACP_CC_PLANET_ORBITS] = COLORCOMMAND_NAMES::CC_PLANET_ORBITS;
	m_color[ACP_CC_PLANET_NAMES] = COLORCOMMAND_NAMES::CC_PLANET_NAMES;
	m_color[ACP_CC_PLANET_TRAILS] = COLORCOMMAND_NAMES::CC_PLANET_TRAILS;
	m_color[ACP_CC_AZIMUTHAL_GRID] = COLORCOMMAND_NAMES::CC_AZIMUTHAL_GRID;
	m_color[ACP_CC_EQUATOR_GRID] = COLORCOMMAND_NAMES::CC_EQUATOR_GRID;
	m_color[ACP_CC_ECLIPTIC_GRID] = COLORCOMMAND_NAMES::CC_ECLIPTIC_GRID;
	m_color[ACP_CC_GALACTIC_GRID] = COLORCOMMAND_NAMES::CC_GALACTIC_GRID;
	m_color[ACP_CC_GALACTIC_GRID] = COLORCOMMAND_NAMES::CC_EQUATOR_LINE;
	m_color[ACP_CC_GALACTIC_LINE] = COLORCOMMAND_NAMES::CC_GALACTIC_LINE;
	m_color[ACP_CC_ECLIPTIC_LINE] = COLORCOMMAND_NAMES::CC_ECLIPTIC_LINE;
	m_color[ACP_CC_MERIDIAN_LINE] = COLORCOMMAND_NAMES::CC_MERIDIAN_LINE;
	m_color[ACP_CC_ZENITH_LINE] = COLORCOMMAND_NAMES::CC_ZENITH_LINE;
	m_color[ACP_CC_POLAR_POINT] = COLORCOMMAND_NAMES::CC_POLAR_POINT;
	m_color[ACP_CC_POLAR_CIRCLE] = COLORCOMMAND_NAMES::CC_POLAR_CIRCLE;
	m_color[ACP_CC_ECLIPTIC_CENTER] = COLORCOMMAND_NAMES::CC_ECLIPTIC_CENTER;
	m_color[ACP_CC_GALACTIC_POLE] = COLORCOMMAND_NAMES::CC_GALACTIC_POLE;
	m_color[ACP_CC_GALACTIC_CENTER] = COLORCOMMAND_NAMES::CC_GALACTIC_CENTER;
	m_color[ACP_CC_VERNAL_POINTS] = COLORCOMMAND_NAMES::CC_VERNAL_POINTS;
	m_color[ACP_CC_ANALEMMA] = COLORCOMMAND_NAMES::CC_ANALEMMA;
	m_color[ACP_CC_ANALEMMA_LINE] = COLORCOMMAND_NAMES::CC_ANALEMMA_LINE;
	m_color[ACP_CC_GREENWICH_LINE] = COLORCOMMAND_NAMES::CC_GREENWICH_LINE;
	m_color[ACP_CC_ARIES_LINE] = COLORCOMMAND_NAMES::CC_ARIES_LINE;
	m_color[ACP_CC_ZODIAC] = COLORCOMMAND_NAMES::CC_ZODIAC;
	m_color[ACP_CC_PERSONAL] = COLORCOMMAND_NAMES::CC_PERSONAL;
	m_color[ACP_CC_PERSONEQ] = COLORCOMMAND_NAMES::CC_PERSONEQ;
	m_color[ACP_CC_NAUTICAL_ALT] = COLORCOMMAND_NAMES::CC_NAUTICAL_ALT;
	m_color[ACP_CC_NAUTICAL_RA] = COLORCOMMAND_NAMES::CC_NAUTICAL_RA;
	m_color[ACP_CC_OBJECT_COORDINATES] = COLORCOMMAND_NAMES::CC_OBJECT_COORDINATES;
	m_color[ACP_CC_MOUSE_COORDINATES] = COLORCOMMAND_NAMES::CC_MOUSE_COORDINATES;
	m_color[ACP_CC_ANGULAR_DISTANCE] = COLORCOMMAND_NAMES::CC_ANGULAR_DISTANCE;
	m_color[ACP_CC_LOXODROMY] = COLORCOMMAND_NAMES::CC_LOXODROMY;
	m_color[ACP_CC_ORTHODROMY] = COLORCOMMAND_NAMES::CC_ORTHODROMY;
	m_color[ACP_CC_VERTICAL_LINE] = COLORCOMMAND_NAMES::CC_VERTICAL_LINE;
	m_color[ACP_CC_NEBULA_NAMES] = COLORCOMMAND_NAMES::CC_NEBULA_NAMES;
	m_color[ACP_CC_NEBULA_CIRCLE] = COLORCOMMAND_NAMES::CC_NEBULA_CIRCLE;
	m_color[ACP_CC_PRECESSION_CIRCLE] = COLORCOMMAND_NAMES::CC_PRECESSION_CIRCLE;
	m_color[ACP_CC_TEXT_USR_COLOR] = COLORCOMMAND_NAMES::CC_TEXT_USR_COLOR;
	m_color[ACP_CC_STAR_TABLE] = COLORCOMMAND_NAMES::CC_STAR_TABLE;

	for (auto it = m_color.begin(); it != m_color.end(); ++it) {
        m_colorToString.emplace(it->second, it->first);
    }

	//make a copy to futur exploitation
	for (const auto& i : m_color) {
		colorList.push_back(i.first);
	}
}

void AppCommandInit::initialiseSetCommand(std::map<const std::string, SCD_NAMES> &m_set, std::map<SCD_NAMES, const std::string> &m_setToString)
{
	m_set[ACP_SC_ATMOSPHERE_FADE_DURATION] = SCD_NAMES::APP_ATMOSPHERE_FADE_DURATION;
	m_set[ACP_SC_AUTO_MOVE_DURATION] = SCD_NAMES::APP_AUTO_MOVE_DURATION;
	m_set[ACP_SC_CONSTELLATION_ART_FADE_DURATION] = SCD_NAMES::APP_CONSTELLATION_ART_FADE_DURATION;
	m_set[ACP_SC_CONSTELLATION_ART_INTENSITY] = SCD_NAMES::APP_CONSTELLATION_ART_INTENSITY;
	m_set[ACP_SC_LIGHT_POLLUTION_LIMITING_MAGNITUDE] = SCD_NAMES::APP_LIGHT_POLLUTION_LIMITING_MAGNITUDE;
	m_set[ACP_SC_HEADING] = SCD_NAMES::APP_HEADING;
	m_set[ACP_SC_HOME_PLANET] = SCD_NAMES::APP_HOME_PLANET;
	m_set[ACP_SC_LANDSCAPE_NAME] = SCD_NAMES::APP_LANDSCAPE_NAME;
	m_set[ACP_SC_LINE_WIDTH] = SCD_NAMES::APP_LINE_WIDTH;
	m_set[ACP_SC_MAX_MAG_NEBULA_NAME] = SCD_NAMES::APP_MAX_MAG_NEBULA_NAME;
	m_set[ACP_SC_MAX_MAG_STAR_NAME] = SCD_NAMES::APP_MAX_MAG_STAR_NAME;
	m_set[ACP_SC_MOON_SCALE] = SCD_NAMES::APP_MOON_SCALE;
	m_set[ACP_SC_SUN_SCALE] = SCD_NAMES::APP_SUN_SCALE;
	m_set[ACP_SC_MILKY_WAY_TEXTURE] = SCD_NAMES::APP_MILKY_WAY_TEXTURE;
	m_set[ACP_SC_SKY_CULTURE] = SCD_NAMES::APP_SKY_CULTURE;
	m_set[ACP_SC_SKY_LOCALE] = SCD_NAMES::APP_SKY_LOCALE;
	m_set[ACP_SC_UI_LOCALE] = SCD_NAMES::APP_UI_LOCALE;
	m_set[ACP_SC_STAR_MAG_SCALE] = SCD_NAMES::APP_STAR_MAG_SCALE;
	m_set[ACP_SC_STAR_SIZE_LIMIT] = SCD_NAMES::APP_STAR_SIZE_LIMIT;
	m_set[ACP_SC_PLANET_SIZE_LIMIT] = SCD_NAMES::APP_PLANET_SIZE_LIMIT;
	m_set[ACP_SC_STAR_SCALE] = SCD_NAMES::APP_STAR_SCALE;
	m_set[ACP_SC_STAR_TWINKLE_AMOUNT] = SCD_NAMES::APP_STAR_TWINKLE_AMOUNT;
	m_set[ACP_SC_STAR_FADER_DURATION] = SCD_NAMES::APP_STAR_FADER_DURATION;
	m_set[ACP_SC_STAR_LIMITING_MAG] = SCD_NAMES::APP_STAR_LIMITING_MAG;
	m_set[ACP_SC_TIME_ZONE] = SCD_NAMES::APP_TIME_ZONE;
	m_set[ACP_SC_AMBIENT_LIGHT] = SCD_NAMES::APP_AMBIENT_LIGHT;
	m_set[ACP_SC_TEXT_FADING_DURATION] = SCD_NAMES::APP_TEXT_FADING_DURATION;
	m_set[ACP_SC_MILKY_WAY_FADER_DURATION] = SCD_NAMES::APP_MILKY_WAY_FADER_DURATION;
	m_set[ACP_SC_MILKY_WAY_INTENSITY] = SCD_NAMES::APP_MILKY_WAY_INTENSITY;
	m_set[ACP_SC_ZOOM_OFFSET] = SCD_NAMES::APP_ZOOM_OFFSET;
	m_set[ACP_SC_STARTUP_TIME_MODE] = SCD_NAMES::APP_STARTUP_TIME_MODE;
	m_set[ACP_SC_DATE_DISPLAY_FORMAT] = SCD_NAMES::APP_DATE_DISPLAY_FORMAT;
	m_set[ACP_SC_TIME_DISPLAY_FORMAT] = SCD_NAMES::APP_TIME_DISPLAY_FORMAT;
	m_set[ACP_SC_MODE] = SCD_NAMES::APP_MODE;
	m_set[ACP_SC_SCREEN_FADER] = SCD_NAMES::APP_SCREEN_FADER;
	m_set[ACP_SC_STALL_RADIUS_UNIT] = SCD_NAMES::APP_STALL_RADIUS_UNIT;
	//m_set[ACP_SC_TULLY_COLOR_MODE] = SCD_NAMES::APP_TULLY_COLOR_MODE;
	m_set[ACP_SC_DATETIME_DISPLAY_POSITION] = SCD_NAMES::APP_DATETIME_DISPLAY_POSITION;
	m_set[ACP_SC_DATETIME_DISPLAY_NUMBER] = SCD_NAMES::APP_DATETIME_DISPLAY_NUMBER;

	for (auto it = m_set.begin(); it != m_set.end(); ++it) {
        m_setToString.emplace(it->second, it->first);
    }

	//make a copy to futur exploitation
	for (const auto& i : m_set) {
		setList.push_back(i.first);
	}
}

template<typename T> typename T::size_type LevensteinDistance(const T &source, const T &target)
{
    if (source.size() > target.size()) {
        return LevensteinDistance(target, source);
    }

    using TSizeType = typename T::size_type;
    const TSizeType min_size = source.size(), max_size = target.size();
    std::vector<TSizeType> lev_dist(min_size + 1);

    for (TSizeType i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (TSizeType j = 1; j <= max_size; ++j) {
        TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (TSizeType i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }
    return lev_dist[min_size];
}

void AppCommandInit::searchNeighbour(const std::string &source, const std::list<std::string> &target)
{
	int distance = 0;
	int minDistance = 99999;
	std::string solution;

	if (isObsoleteToken(source))
		return;

	for(const auto &i : target) {
		distance = LevensteinDistance(source,i);
		if (distance < minDistance) {
			minDistance = distance;
			solution = i;
		}
	}
	std::string helpMsg = source + " is unknown. Did you mean "+ solution + " ?";
	cLog::get()->write( helpMsg,LOG_TYPE::L_DEBUG, LOG_FILE::SCRIPT );
	//std::cout << source << " a pour proche valeur " << solution << std::endl;
}
