/*
 * WiVRn VR streaming
 * Copyright (C) 2025  Awzri <awzri@awzricat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "wivrn_packets.h"
#include "xr/htc_oxr_ext.h"
#include "xr/instance.h"
#include "xr/session.h"
#include "xr/space.h"
#include <cstdint>
#include <vector>
#include <openxr/openxr.h>

namespace xr
{

class vive_xr_tracker
{
	bool is_active = false;
	xr::space space;

public:
	const uint8_t id;

	vive_xr_tracker(uint8_t id, xr::space s);
	wivrn::from_headset::tracking::pose get_pose(instance & inst, session & session, XrTime time, XrSpace & reference);
	void set_active(bool active);
	bool get_active();
	xr::space * get_space();
};

void xr_tracker_update_active(instance & inst, session & session);
std::vector<XrPath> xr_tracker_get_paths(instance & inst, XrPath user_path = XR_NULL_PATH);
std::vector<std::string> xr_tracker_get_roles(instance & inst, session & session);
std::vector<wivrn::from_headset::tracking::motion_tracker> xr_tracker_compose_packet(instance & inst, session & session, XrTime time, XrSpace reference, std::vector<xr::vive_xr_tracker> & trackers);
} // namespace xr
