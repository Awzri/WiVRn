/*
 * WiVRn VR streaming
 * Copyright (C) 2024  Guillaume Meunier <guillaume.meunier@centraliens.net>
 * Copyright (C) 2024  Patrick Nicolas <patricknicolas@laposte.net>
 * Copyright (C) 2024  galister <galister@librevr.org>
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

#include "wivrn_htc_xr_tracker.h"

#include "driver/wivrn_session.h"
#include "wivrn_packets.h"
#include "xrt/xrt_defines.h"
#include "xrt/xrt_device.h"

#include "util/u_logging.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <openxr/openxr.h>

namespace wivrn
{

static void wivrn_xr_tracker_destroy(xrt_device * xdev);

static xrt_result_t wivrn_xr_tracker_update_inputs(xrt_device * xdev)
{
	static_cast<wivrn_xr_tracker *>(xdev)->update_inputs();
	return XRT_SUCCESS;
}

static xrt_result_t wivrn_xr_tracker_get_tracked_pose(xrt_device * xdev,
                                                       xrt_input_name name,
                                                       int64_t at_timestamp_ns,
                                                       xrt_space_relation * out_relation)
{
	*out_relation = static_cast<wivrn_xr_tracker *>(xdev)->get_tracked_pose(name, at_timestamp_ns);
	return XRT_SUCCESS;
}

wivrn_xr_tracker::wivrn_xr_tracker(xrt_device * hmd, uint8_t id) :
        xrt_device{}, tracker_pose(device_id::GENERIC_TRACKER), id{}
{
	xrt_device * base = this;
	base->tracking_origin = hmd->tracking_origin;

	base->update_inputs = wivrn_xr_tracker_update_inputs;
	base->get_tracked_pose = wivrn_xr_tracker_get_tracked_pose;
	base->destroy = wivrn_xr_tracker_destroy;
	name = XRT_DEVICE_VIVE_TRACKER;
	device_type = XRT_DEVICE_TYPE_BODY_TRACKER;
	body_tracking_supported = true;

	// Print name.
	strcpy(str, "WiVRn Vive XR Tracker");
	strcpy(serial, "WiVRn Vive XR Tracker");

	tracker_input.active = true;
	tracker_input.name = XRT_INPUT_VIVE_TRACKER_GRIP_POSE;

	// Setup input.
	inputs = &tracker_input;
	input_count = 1;
}

void wivrn_xr_tracker::update_inputs()
{
	// Empty
}

xrt_space_relation wivrn_xr_tracker::get_tracked_pose(xrt_input_name name, int64_t at_timestamp_ns)
{
	if (name == XRT_INPUT_VIVE_TRACKER_GRIP_POSE)
	{
		auto [_, relation] = tracker_pose.get_at(at_timestamp_ns);
		return relation;
	}

	U_LOG_E("Unknown input name");
	return {};
}

void wivrn_xr_tracker::update_tracking(const from_headset::tracking & tracking, const clock_offset & offset)
{
	tracker_pose.update_tracking(tracking, offset);
}

/*
 *
 * Functions
 *
 */

static void wivrn_xr_tracker_destroy(xrt_device * xdev)
{
}

} // namespace wivrn
