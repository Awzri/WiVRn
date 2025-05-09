/*
 * WiVRn VR streaming
 * Copyright (C) 2022  Guillaume Meunier <guillaume.meunier@centraliens.net>
 * Copyright (C) 2022  Patrick Nicolas <patricknicolas@laposte.net>
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

#include "openxr/openxr.h"
#include "utils/handle.h"
#include <variant>

static int XR_TYPE_SYSTEM_PASSTHROUGH_CONFIGURATION_PROPERTIES_HTC = 1000328000;
static int XR_TYPE_PASSTHROUGH_CONFIGURATION_BASE_HEADER_HTC = 1000328001;
static int XR_TYPE_PASSTHROUGH_CONFIGURATION_IMAGE_RATE_HTC = 1000328002;
static int XR_TYPE_PASSTHROUGH_CONFIGURATION_IMAGE_QUALITY_HTC = 1000328003;

typedef struct XrPassthroughConfigurationImageRateHTC
{
	int type;
	const void * XR_MAY_ALIAS next;
	float srcImageRate;
	float dstImageRate;
} XrPassthroughConfigurationImageRateHTC;
typedef struct XrPassthroughConfigurationImageQualityHTC
{
	int type;
	const void * XR_MAY_ALIAS next;
	float scale;
} XrPassthroughConfigurationImageQualityHTC;
typedef XrResult(XRAPI_PTR * PFN_xrEnumeratePassthroughImageRatesHTC)(
    XrSession session,
    uint32_t imageRateCapacityInput,
    uint32_t * imageRateCountOutput,
    XrPassthroughConfigurationImageRateHTC * imageRates);
typedef XrResult(XRAPI_PTR * PFN_xrGetPassthroughConfigurationHTC)(
    XrSession session,
    const void * XR_MAY_ALIAS config);
typedef XrResult(XRAPI_PTR * PFN_xrSetPassthroughConfigurationHTC)(
    XrSession session,
    const void * XR_MAY_ALIAS config);
static PFN_xrEnumeratePassthroughImageRatesHTC xrEnumeratePassthroughImageRatesHTC{};
static PFN_xrGetPassthroughConfigurationHTC xrGetPassthroughConfigurationHTC{};
static PFN_xrSetPassthroughConfigurationHTC xrSetPassthroughConfigurationHTC{};

namespace xr
{
class instance;
class session;

XrResult destroy_passthrough_layer_fb(XrPassthroughLayerFB);
XrResult destroy_passthrough_fb(XrPassthroughFB);
XrResult destroy_passthrough_htc(XrPassthroughHTC);

class passthrough_layer_fb : public utils::handle<XrPassthroughLayerFB, destroy_passthrough_layer_fb>
{
public:
	passthrough_layer_fb(instance &, session &, const XrPassthroughLayerCreateInfoFB &);
};

class passthrough_fb : public utils::handle<XrPassthroughFB, destroy_passthrough_fb>
{
	PFN_xrPassthroughStartFB xrPassthroughStartFB{};
	PFN_xrPassthroughPauseFB xrPassthroughPauseFB{};
	PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB{};
	PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB{};

	passthrough_layer_fb passthrough_layer;
	XrCompositionLayerPassthroughFB composition_layer;

public:
	passthrough_fb(instance &, session &);

	void start();
	void pause();
	XrCompositionLayerBaseHeader * layer()
	{
		return (XrCompositionLayerBaseHeader *)&composition_layer;
	}
};

class passthrough_htc : public utils::handle<XrPassthroughHTC, destroy_passthrough_htc>
{
	XrCompositionLayerPassthroughHTC composition_layer;

public:
	passthrough_htc(instance &, session &);
	XrCompositionLayerBaseHeader * layer()
	{
		return (XrCompositionLayerBaseHeader *)&composition_layer;
	}
};

class passthrough_alpha_blend
{
};

using passthrough = std::variant<std::monostate, passthrough_fb, passthrough_htc, passthrough_alpha_blend>;

} // namespace xr
