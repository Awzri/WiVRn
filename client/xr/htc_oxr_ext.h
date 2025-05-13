#pragma once

#include <openxr/openxr.h>

#define XR_HTC_VIVE_XR_TRACKER_INTERACTION_EXTENSION_NAME "XR_HTC_vive_xr_tracker_interaction"

#define XR_HTC_PASSTHROUGH_CONFIGURATION_EXTENSION_NAME "XR_HTC_passthrough_configuration"

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

#define XR_HTC_PATH_ENUMERATION_EXTENSION_NAME "XR_HTC_path_enumeration"

typedef struct XrPathsForInteractionProfileEnumerateInfoHTC
{
	XrStructureType type;
	const void * XR_MAY_ALIAS next;
	XrPath interactionProfile;
	XrPath userPath;
} XrPathsForInteractionProfileEnumerateInfoHTC;

typedef XrResult(XRAPI_PTR * PFN_xrEnumeratePathsForInteractionProfileHTC)(XrInstance instance, XrPathsForInteractionProfileEnumerateInfoHTC createInfo, uint32_t pathCapacityInput, uint32_t * pathCountOutput, XrPath * paths);
static PFN_xrEnumeratePathsForInteractionProfileHTC xrEnumeratePathsForInteractionProfileHTC{};

#define XR_HTC_COMPOSITION_LAYER_EXTRA_SETTINGS_EXTENSION_NAME "XR_HTC_composition_layer_extra_settings"

// This causes more problems than it solves.
// We'll just use numerical values for now.
/* enum XrSharpenSupersampleModeHTC
{
    NONE = -1,
	FAST = 0,
	NORMAL = 1,
	QUALITY = 2,
	AUTO = 3
	}; */

typedef struct XrCompositionLayerSharpeningSettingHTC
{
	int type;
	const void * XR_MAY_ALIAS next;
	int /*XrSharpeningModeHTC*/ mode;
	float sharpeningLevel;
} XrCompositionLayerSharpeningSettingHTC;
typedef struct XrCompositionLayerSuperSamplingSettingHTC
{
	int type;
	const void * XR_MAY_ALIAS next;
	int /*XrSuperSamplingModeHTC*/ mode;
} XrCompositionLayerSuperSamplingSettingHTC;
