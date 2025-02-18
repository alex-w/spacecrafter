/*
 * Copyright (C) 2020 Elitit-40
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

// Class which parses an init file
// C++ warper for the iniparser free library from N.Devillard

#ifndef _VAR_FROM_CONFIG_INI_
#define _VAR_FROM_CONFIG_INI_

//SCS_X mean Spacecrafter Section X
#define SCS_MAIN                             "main"
#define SCS_IO                               "io"
#define SCS_VIDEO                            "video"
#define SCS_RENDERING                        "rendering"
#define SCS_LOCALIZATION                     "localization"
#define SCS_STARS                            "stars"
#define SCS_GUI                              "gui"
#define SCS_FONT                             "font"
#define SCS_TUI                              "tui"
#define SCS_LANDSCAPE                        "landscape"
#define SCS_COLOR                            "color"
#define SCS_VIEWING                          "viewing"
#define SCS_NAVIGATION                       "navigation"
#define SCS_ASTRO                            "astro"
#define SCS_INIT_LOCATION                    "init_location"

// SCK_Y mean Spacecfrater Key Y
#define SCK_VERSION                         "version"
#define SCK_DEBUG                           "debug"
#define SCK_DEBUG_LAYER                     "debug_layer"
#define SCK_TEX_CACHE                       "texture_caching"
#define SCK_TEXTURE_LOADING                 "texture_loading"
#define SCK_LOW_MEMORY                      "low_memory"
#define SCK_LOG                             "write_log"
#define SCK_MILKYWAY_IRIS                   "milkyway_iris"
// #define SCK_FLAG_OPTOMA                     "flag_optoma"
#define SCK_CPU_INFO                        "cpu_info"
#define SCK_FLAG_ALWAYS_VISIBLE             "flag_always_visible"
#define SCK_STATISTICS                      "query_statistics"
#define SCK_BUILDER_THREADS                 "builder_threads"

#define SCK_ENABLE_MKFIFO                   "enable_mkfifo"
#define SCK_ENABLE_TCP                      "enable_tcp"
#define SCK_TCP_PORT_IN                     "tcp_port_in"
#define SCK_TCP_BUFFER_IN_SIZE              "tcp_buffer_in_size"
#define SCK_MKFIFO_FILE_IN                  "mkfifo_file_in"
#define SCK_MKFIFO_BUFFER_IN_SIZE           "mkfifo_buffer_in_size"
#define SCK_MPLAYER_MKFIFO_NAME             "mplayer_mkfifo_name"
#define SCK_FLAG_MASTERPUT                  "flag_masterput"
#define SCK_VIDEO_CODEC_THREADS             "video_codec_threads"

#define SCK_AUTOSCREEN                      "autoscreen"
#define SCK_FULLSCREEN                      "fullscreen"
#define SCK_REMOTE_DISPLAY                  "remote_display"
#define SCK_KEEP_EMPTY_WINDOW               "keep_empty_window"
#define SCK_RENDER_SIZE                     "render_size"
#define SCK_SCREEN_W                        "screen_w"
#define SCK_SCREEN_H                        "screen_h"
//#define SCK_BBP_MODE                        "bbp_mode"
#define SCK_MAXIMUM_FPS                     "maximum_fps"
#define SCK_REC_VIDEO_FPS                   "rec_video_fps"
#define SCK_AUDIO_FREQUENCY                 "audio_frequency"
#define SCK_AUDIO_CHUNKSIZE                 "audio_chunksize"
#define SCK_AUDIO_CHANNELS                  "audio_channels"

#define SCK_FLAG_ANTIALIAS_LINES            "flag_antialias_lines"
#define SCK_ANTIALIASING                    "antialiasing"
#define SCK_LINE_WIDTH                      "line_width"
#define SCK_FLUSH_FRAMES                    "flush_frames"
#define SCK_ANISOTROPY                      "anisotropy"
#define SCK_LANDSCAPE_SLICES                "landscape_slices"
#define SCK_LANDSCAPE_STACKS                "landscape_stacks"
#define SCK_MIN_TES_LEVEL                   "min_tes_level"
#define SCK_MAX_TES_LEVEL                   "max_tes_level"
#define SCK_PLANET_ALTIMETRY_LEVEL          "planet_altimetry_level"
#define SCK_EARTH_ALTIMETRY_LEVEL           "earth_altimetry_level"
#define SCK_MOON_ALTIMETRY_LEVEL            "moon_altimetry_level"
#define SCK_RINGS_LOW                       "rings_low"
#define SCK_RINGS_MEDIUM                    "rings_medium"
#define SCK_RINGS_HIGH                      "rings_high"
#define SCK_OORT_ELEMENTS                   "oort_elements"
#define SCK_SHADOW_RESOLUTION               "shadow_resolution"
#define SCK_SELF_SHADOW_RESOLUTION          "self_shadow_resolution"
#define SCK_EXPERIMENTAL_SHADOWS            "experimental_shadows"
#define SCK_MAX_SHADOW_CAST                 "max_shadow_cast"

#define SCK_SKY_CULTURE                     "sky_culture"
#define SCK_SKY_LOCALE                      "sky_locale"
#define SCK_TIME_DISPLAY_FORMAT             "time_display_format"
#define SCK_DATE_DISPLAY_FORMAT             "date_display_format"
#define SCK_APP_LOCALE                      "app_locale"
#define SCK_TIME_ZONE                       "time_zone"
#define SCK_STAR_SCALE                      "star_scale"
#define SCK_STAR_MAG_SCALE                  "star_mag_scale"
#define SCK_STAR_TWINKLE_AMOUNT             "star_twinkle_amount"
#define SCK_MAX_MAG_STAR_NAME               "max_mag_star_name"
#define SCK_FLAG_STAR_TWINKLE               "flag_star_twinkle"
#define SCK_STAR_LIMITING_MAG               "star_limiting_mag"
#define SCK_MAG_CONVERTER_MIN_FOV           "mag_converter_min_fov"
#define SCK_MAG_CONVERTER_MAX_FOV           "mag_converter_max_fov"
#define SCK_MAG_CONVERTER_MAG_SHIFT         "mag_converter_mag_shift"
#define SCK_MAG_CONVERTER_MAX_MAG           "mag_converter_max_mag"
#define SCK_ILLUMINATE_SIZE                 "illuminate_size"
#define SCK_FLAG_SHOW_FPS                   "flag_show_fps"
#define SCK_FLAG_SHOW_FOV                   "flag_show_fov"
#define SCK_FLAG_SHOW_LATLON                "flag_show_latlon"
#define SCK_FLAG_NUMBER_PRINT               "flag_number_print"
#define SCK_DATETIME_DISPLAY_POSITION       "datetime_display_position"
#define SCK_OBJECT_INFO_DISPLAY_POSITION    "object_info_display_position"
#define SCK_FLAG_SHOW_PLANETNAME            "flag_show_planetname"
#define SCK_MOUSE_CURSOR_TIMEOUT            "mouse_cursor_timeout"
#define SCK_MENU_DISPLAY_POSITION           "menu_display_position"
#define SCK_FLAG_MOUSE_USABLE_IN_SCRIPT     "flag_mouse_usable_in_script"
#define SCK_FONT_RESOLUTION_SIZE            "font_resolution_size"
#define SCK_FONT_GENERAL_NAME               "font_general_name"
// #define SCK_FONT_GENERAL_SIZE               "font_general_size"
#define SCK_FONT_MENU_NAME                  "font_menu_name"
#define SCK_FONT_MENUTUI_SIZE               "font_menutui_size"
#define SCK_FONT_PLANET_NAME                "font_planet_name"
#define SCK_FONT_PLANET_SIZE                "font_planet_size"
#define SCK_FONT_CONSTELLATION_NAME         "font_constellation_name"
#define SCK_FONT_CONSTELLATION_SIZE         "font_constellation_size"
#define SCK_FONT_DISPLAY_NAME               "font_display_name"
#define SCK_FONT_DISPLAY_SIZE               "font_display_size"
#define SCK_FONT_CARDINALPOINTS_SIZE        "font_cardinalpoints_size"
#define SCK_FONT_CARDINALPOINTS_NAME        "font_cardinalpoints_name"
#define SCK_FONT_GRID_NAME                  "font_grid_name"
#define SCK_FONT_GRID_SIZE                  "font_grid_size"
#define SCK_FONT_LINES_NAME                 "font_lines_name"
#define SCK_FONT_LINE_SIZE                  "font_line_size"
#define SCK_FONT_HIPSTARS_NAME              "font_hip_stars_name"
#define SCK_FONT_HIPSTARS_SIZE              "font_hip_stars_size"
#define SCK_FONT_NEBULAS_NAME               "font_nebulas_name"
#define SCK_FONT_NEBULAS_SIZE               "font_nebulas_size"
#define SCK_FONT_TEXT_NAME                  "font_text_name"
#define SCK_FONT_TEXT_SIZE                  "font_text_size"
#define SCK_FONT_MENUGUI_SIZE               "font_menugui_size"
#define SCK_FLAG_ENABLE_TUI_MENU            "flag_enable_tui_menu"
#define SCK_FLAG_SHOW_GRAVITY_UI            "flag_show_gravity_ui"
#define SCK_FLAG_SHOW_TUI_DATETIME          "flag_show_tui_datetime"
#define SCK_FLAG_SHOW_TUI_SHORT_OBJ_INFO    "flag_show_tui_short_obj_info"
#define SCK_TEXT_UI                         "text_ui"
#define SCK_TEXT_TUI_ROOT                   "text_tui_root"
#define SCK_FLAG_LANDSCAPE                  "flag_landscape"
#define SCK_FLAG_FOG                        "flag_fog"
#define SCK_FLAG_ATMOSPHERE                 "flag_atmosphere"

#define SCK_AZIMUTHAL_COLOR                 "azimuthal_color"
#define SCK_EQUATORIAL_COLOR                "equatorial_color"
#define SCK_ECLIPTIC_COLOR                  "ecliptic_color"
#define SCK_GALACTIC_COLOR                  "galactic_color"
#define SCK_ECLIPTIC_COLOR                  "ecliptic_color"
#define SCK_ECLIPTIC_CENTER_COLOR           "ecliptic_center_color"
#define SCK_GALACTIC_CENTER_COLOR           "galactic_center_color"
#define SCK_GALACTIC_POLE_COLOR             "galactic_pole_color"
#define SCK_NEBULA_LABEL_COLOR              "nebula_label_color"
#define SCK_NEBULA_CIRCLE_COLOR             "nebula_circle_color"
#define SCK_PRECESSION_CIRCLE_COLOR         "precession_circle_color"
#define SCK_CIRCUMPOLAR_CIRCLE_COLOR        "circumpolar_circle_color"
#define SCK_OORT_COLOR                      "oort_color"
#define SCK_VERNAL_POINTS_COLOR             "vernal_points_color"
#define SCK_PLANET_HALO_COLOR               "planet_halo_color"
#define SCK_PLANET_NAMES_COLOR              "planet_names_color"
#define SCK_PLANET_ORBITS_COLOR             "planet_orbits_color"
#define SCK_OBJECT_TRAILS_COLOR             "object_trails_color"
#define SCK_EQUATOR_COLOR                   "equator_color"
#define SCK_CONST_LINES_COLOR               "const_lines_color"
#define SCK_CONST_LINES3D_COLOR             "const_lines3D_color"
#define SCK_CONST_BOUNDARY_COLOR            "const_boundary_color"
#define SCK_CONST_NAMES_COLOR               "const_names_color"
#define SCK_CONST_ART_COLOR                 "const_art_color"
#define SCK_ANALEMMA_LINE_COLOR             "analemma_line_color"
#define SCK_ANALEMMA_COLOR                  "analemma_color"
#define SCK_ARIES_COLOR                     "aries_color"
#define SCK_CARDINAL_COLOR                  "cardinal_color"
#define SCK_ECLIPTIC_CENTER_COLOR           "ecliptic_center_color"
#define SCK_GALACTIC_POLE_COLOR             "galactic_pole_color"
#define SCK_GALACTIC_CENTER_COLOR           "galactic_center_color"
#define SCK_GREENWICH_COLOR                 "greenwich_color"
#define SCK_MERIDIAN_COLOR                  "meridian_color"
#define SCK_PERSONAL_COLOR                  "personal_color"
#define SCK_PERSONEQ_COLOR                  "personeq_color"
#define SCK_NAUTICAL_ALT_COLOR              "nautical_alt_color"
#define SCK_NAUTICAL_RA_COLOR               "nautical_ra_color"
#define SCK_OBJECT_COORDINATES_COLOR        "object_coordinates_color"
#define SCK_MOUSE_COORDINATES_COLOR         "mouse_coordinates_color"
#define SCK_ANGULAR_DISTANCE_COLOR          "angular_distance_color"
#define SCK_LOXODROMY_COLOR                 "loxodromy_color"
#define SCK_ORTHODROMY_COLOR                "orthodromy_color"
#define SCK_POLAR_COLOR                     "polar_color"
#define SCK_TEXT_USR_COLOR                  "text_usr_color"
#define SCK_VERNAL_POINTS_COLOR             "vernal_points_color"
#define SCK_VERTICAL_COLOR                  "vertical_color"
#define SCK_ZENITH_COLOR                    "zenith_color"
#define SCK_ZODIAC_COLOR                    "zodiac_color"

#define SCK_NEBULA_PICTO_SIZE               "nebula_picto_size"
#define SCK_ATMOSPHERE_FADE_DURATION        "atmosphere_fade_duration"
#define SCK_MOON_BRIGHTNESS                 "moon_brightness"
#define SCK_SUN_BRIGHTNESS                  "sun_brightness"
#define SCK_FLAG_CONSTELLATION_DRAWING      "flag_constellation_drawing"
#define SCK_FLAG_CONSTELLATION_NAME         "flag_constellation_name"
#define SCK_FLAG_CONSTELLATION_BOUNDARIES   "flag_constellation_boundaries"
#define SCK_FLAG_CONSTELLATION_ART          "flag_constellation_art"
#define SCK_FLAG_CONSTELLATION_PICK         "flag_constellation_pick"
#define SCK_CONSTELLATION_ART_INTENSITY     "constellation_art_intensity"
#define SCK_CONSTELLATION_ART_FADE_DURATION "constellation_art_fade_duration"
#define SCK_FLAG_AZIMUTAL_GRID              "flag_azimutal_grid"
#define SCK_FLAG_EQUATORIAL_GRID            "flag_equatorial_grid"
#define SCK_FLAG_ECLIPTIC_GRID              "flag_ecliptic_grid"
#define SCK_FLAG_GALACTIC_GRID              "flag_galactic_grid"
#define SCK_FLAG_EQUATOR_LINE               "flag_equator_line"
#define SCK_FLAG_GALACTIC_LINE              "flag_galactic_line"
#define SCK_FLAG_ECLIPTIC_LINE              "flag_ecliptic_line"
#define SCK_FLAG_PRECESSION_CIRCLE          "flag_precession_circle"
#define SCK_FLAG_CIRCUMPOLAR_CIRCLE         "flag_circumpolar_circle"
#define SCK_FLAG_TROPIC_LINES               "flag_tropic_lines"
#define SCK_FLAG_MERIDIAN_LINE              "flag_meridian_line"
#define SCK_FLAG_ZENITH_LINE                "flag_zenith_line"
#define SCK_FLAG_POLAR_CIRCLE               "flag_polar_circle"
#define SCK_FLAG_POLAR_POINT                "flag_polar_point"
#define SCK_FLAG_ECLIPTIC_CENTER            "flag_ecliptic_center"
#define SCK_FLAG_GALACTIC_POLE              "flag_galactic_pole"
#define SCK_FLAG_GALACTIC_CENTER            "flag_galactic_center"
#define SCK_FLAG_VERNAL_POINTS              "flag_vernal_points"
#define SCK_FLAG_ANALEMMA_LINE              "flag_analemma_line"
#define SCK_FLAG_ANALEMMA                   "flag_analemma"
#define SCK_FLAG_ARIES_LINE                 "flag_aries_line"
#define SCK_FLAG_ZODIAC                     "flag_zodiac"
#define SCK_FLAG_CARDINAL_POINTS            "flag_cardinal_points"
#define SCK_FLAG_VERTICAL_LINE              "flag_vertical_line"
#define SCK_FLAG_GREENWICH_LINE             "flag_greenwich_line"
#define SCK_FLAG_PERSONAL                   "flag_personal"
#define SCK_FLAG_PERSONEQ                   "flag_personeq"
#define SCK_FLAG_SKIP_PAUSE                 "flag_skip_pause"
#define SCK_FLAG_IMAGE_COMPRESSION_LOSS     "flag_image_compression_loss"
#define SCK_FLAG_NAUTICAL_RA                "flag_nautical_ra"
#define SCK_FLAG_NAUTICAL_ALT               "flag_nautical_alt"
#define SCK_FLAG_OBJECT_COORDINATES         "flag_object_coordinates"
#define SCK_FLAG_MOUSE_COORDINATES          "flag_mouse_coordinates"
#define SCK_FLAG_ANGULAR_DISTANCE           "flag_angular_distance"
#define SCK_FLAG_LOXODROMY                  "flag_loxodromy"
#define SCK_FLAG_ORTHODROMY                 "flag_orthodromy"
#define SCK_FLAG_OORT                       "flag_oort"
#define SCK_FLAG_MOON_SCALED                "flag_moon_scaled"
#define SCK_FLAG_SUN_SCALED                 "flag_sun_scaled"
#define SCK_FLAG_ATMOSPHERIC_REFRACTION     "flag_atmospheric_refraction"
#define SCK_MOON_SCALE                      "moon_scale"
#define SCK_SUN_SCALE                       "sun_scale"
#define SCK_LIGHT_POLLUTION_LIMITING_MAGNITUDE      "light_pollution_limiting_magnitude"

#define SCK_FLAG_NAVIGATION                 "flag_navigation"
#define SCK_FLAG_ASTRONOMICAL               "flag_astronomical"
#define SCK_LOW_RES                         "low_resolution"
#define SCK_LOW_RES_MAX                     "low_resolution_max"
#define SCK_PRESET_SKY_TIME                 "preset_sky_time"
#define SCK_AUTO_MOVE_DURATION              "auto_move_duration"
#define SCK_DAY_KEY_MODE                    "day_key_mode"
#define SCK_FLAG_ENABLE_MOVE_KEYS           "flag_enable_move_keys"
#define SCK_FLAG_ENABLE_ZOOM_KEYS           "flag_enable_zoom_keys"
#define SCK_FLAG_MANUAL_ZOOM                "flag_manual_zoom"
#define SCK_HEADING                         "heading"
#define SCK_INIT_FOV                        "init_fov"
#define SCK_INIT_VIEW_POS                   "init_view_pos"
#define SCK_MOUSE_ZOOM                      "mouse_zoom"
#define SCK_MOVE_SPEED                      "move_speed"
#define SCK_STARTUP_TIME_MODE               "startup_time_mode"
#define SCK_VIEW_OFFSET                     "view_offset"
#define SCK_VIEWING_MODE                    "viewing_mode"
#define SCK_ZOOM_SPEED                      "zoom_speed"
#define SCK_STALL_RADIUS_UNIT               "stall_radius_unit"
#define SCK_FLAG_STARS                      "flag_stars"
#define SCK_FLAG_STAR_NAME                  "flag_star_name"
#define SCK_FLAG_STAR_LINES                 "flag_star_lines"
#define SCK_FLAG_PLANETS                    "flag_planets"
#define SCK_FLAG_PLANETS_HINTS              "flag_planets_hints"
#define SCK_FLAG_PLANETS_ORBITS             "flag_planets_orbits"
#define SCK_FLAG_NEBULA                     "flag_nebula"
#define SCK_FLAG_MILKY_WAY                  "flag_milky_way"
#define SCK_FLAG_ZODIACAL_LIGHT             "flag_zodiacal_light"
#define SCK_FLAG_BRIGHT_NEBULAE             "flag_bright_nebulae"
#define SCK_MILKY_WAY_FADER_DURATION        "milky_way_fader_duration"
#define SCK_MILKY_WAY_INTENSITY             "milky_way_intensity"
#define SCK_ZODIACAL_INTENSITY              "zodiacal_intensity"
#define SCK_MILKY_WAY_TEXTURE               "milky_way_texture"
#define SCK_MILKY_WAY_IRIS_TEXTURE          "milky_way_iris_texture"
#define SCK_ZODIACAL_LIGHT_TEXTURE          "zodiacal_light_texture"
#define SCK_FLAG_NEBULA_HINTS               "flag_nebula_hints"
#define SCK_FLAG_NEBULA_NAMES               "flag_nebula_names"
#define SCK_MAX_MAG_NEBULA_NAME             "max_mag_nebula_name"
#define SCK_FLAG_OBJECT_TRAILS              "flag_object_trails"
#define SCK_FLAG_LIGHT_TRAVEL_TIME          "flag_light_travel_time"
#define SCK_PLANET_SIZE_MARGINAL_LIMIT      "planet_size_marginal_limit"
#define SCK_STAR_SIZE_LIMIT                 "star_size_limit"
#define SCK_METEOR_RATE                     "meteor_rate"
#define SCK_LANDSCAPE_NAME                  "landscape_name"
#define SCK_NAME                            "name"
#define SCK_HOME_PLANET                     "home_planet"
#define SCK_ALTITUDE                        "altitude"
#define SCK_LATITUDE                        "latitude"
#define SCK_LONGITUDE                       "longitude"

#define SCK_FLAG_STAR_PICK                  "flag_star_pick"
#define SCK_NAUTICAL_ALT                    "nautical_alt"
#define SCK_NAUTICAL_RA                     "nautical_ra"
#define SCK_OBJECT_COORDINATES              "object_coordinates"
#define SCK_MOUSE_COORDINATES               "mouse_coordinates"
#define SCK_ANGULAR_DISTANCE                "angular_distance"
#define SCK_LOXODROMY                       "loxodromy"
#define SCK_ORTHODROMY                      "orthodromy"
#define SCK_VERTICAL_LINE                   "vertical_line"

#endif
