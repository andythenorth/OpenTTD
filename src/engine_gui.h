/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file engine_gui.h %Engine GUI functions, used by build_vehicle_gui and autoreplace_gui */

#ifndef ENGINE_GUI_H
#define ENGINE_GUI_H

#include "engine_type.h"
#include "group_type.h"
#include "newgrf_badge_gui.h"
#include "sortlist_type.h"
#include "gfx_type.h"
#include "vehicle_type.h"
#include "engine_base.h"

struct GUIEngineListItem {
	EngineID engine_id;       ///< Engine to display in build purchase list
	EngineID variant_id;      ///< Variant group of the engine.
	EngineDisplayFlags flags; ///< Flags for toggling/drawing (un)folded status and controlling indentation.
	uint8_t indent; ///< Display indentation level.
	uint16_t level_mask; ///< Mask of level continuations.

	GUIEngineListItem(EngineID engine_id, EngineID variant_id, EngineDisplayFlags flags, uint8_t indent) : engine_id(engine_id), variant_id(variant_id), flags(flags), indent(indent), level_mask(0) {}
};

typedef GUIList<GUIEngineListItem, std::nullptr_t, CargoType> GUIEngineList;

typedef bool EngList_SortTypeFunction(const GUIEngineListItem&, const GUIEngineListItem&); ///< argument type for #EngList_Sort.
void EngList_Sort(GUIEngineList &el, EngList_SortTypeFunction compare);
void EngList_SortPartial(GUIEngineList &el, EngList_SortTypeFunction compare, size_t begin, size_t num_items);

StringID GetEngineCategoryName(EngineID engine);
std::string GetEngineInfoString(EngineID engine);

void DrawVehicleEngine(int left, int right, int preferred_x, int y, EngineID engine, PaletteID pal, EngineImageType image_type);
void DrawTrainEngine(int left, int right, int preferred_x, int y, EngineID engine, PaletteID pal, EngineImageType image_type);
void DrawRoadVehEngine(int left, int right, int preferred_x, int y, EngineID engine, PaletteID pal, EngineImageType image_type);
void DrawShipEngine(int left, int right, int preferred_x, int y, EngineID engine, PaletteID pal, EngineImageType image_type);
void DrawAircraftEngine(int left, int right, int preferred_x, int y, EngineID engine, PaletteID pal, EngineImageType image_type);

extern bool _engine_sort_direction;
extern uint8_t _engine_sort_last_criteria[];
extern bool _engine_sort_last_order[];
extern bool _engine_sort_show_hidden_engines[];
extern const std::initializer_list<const StringID> _engine_sort_listing[];
extern EngList_SortTypeFunction * const _engine_sort_functions[][11];

/* Functions in build_vehicle_gui.cpp */
uint GetEngineListHeight(VehicleType type);
void DisplayVehicleSortDropDown(Window *w, VehicleType vehicle_type, int selected, WidgetID button);
void DrawEngineList(VehicleType type, const Rect &r, const GUIEngineList &eng_list, const Scrollbar &sb, EngineID selected_id, bool show_count, GroupID selected_group, const GUIBadgeClasses &badge_classes);
void GUIEngineListAddChildren(GUIEngineList &dst, const GUIEngineList &src, EngineID parent = EngineID::Invalid(), uint8_t indent = 0);

#endif /* ENGINE_GUI_H */
