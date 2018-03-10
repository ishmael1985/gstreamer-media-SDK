/*
 *  Copyright (C) 2011-2014 Intel Corporation
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@intel.com>
 *  Copyright (C) 2016 Intel Corporation
 *    Author: Ishmael Visayana Sameen <ishmael.visayana.sameen@intel.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA
 */

#ifndef GST_MFX_PLUGIN_UTIL_H
#define GST_MFX_PLUGIN_UTIL_H

#include "gstmfxvideomemory.h"
#include <gst-libs/mfx/gstmfxtaskaggregator.h>

#ifdef HAVE_GST_GL_LIBS
# include <gst/gl/gstglcontext.h>
#endif // HAVE_GST_GL_LIBS

 /* Helpers to build video caps */
typedef enum
{
  GST_MFX_CAPS_FEATURE_NOT_NEGOTIATED,
  GST_MFX_CAPS_FEATURE_SYSTEM_MEMORY,
  GST_MFX_CAPS_FEATURE_MFX_SURFACE,
  GST_MFX_CAPS_FEATURE_GL_MEMORY,
} GstMfxCapsFeature;

#ifdef WITH_LIBVA_BACKEND
# if MSDK_CHECK_VERSION(1,25)
# if !GST_CHECK_VERSION(1,9,1)
# define GST_MFX_MAKE_INPUT_SURFACE_CAPS        \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, ENCODED, YUY2 }")

# define GST_MFX_MAKE_OUTPUT_SURFACE_CAPS       \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, ENCODED, YUY2 }")

# define GST_MFX_SUPPORTED_INPUT_FORMATS \
    "{ NV12, YV12, I420, UYVY, YUY2, BGRA, BGRx, ENCODED }"

# define GST_MFX_SUPPORTED_OUTPUT_FORMATS \
    "{ NV12, BGRA, ENCODED, YUY2 }"
# else
# define GST_MFX_MAKE_INPUT_SURFACE_CAPS        \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, P010_10LE, YUY2 }")

# define GST_MFX_MAKE_OUTPUT_SURFACE_CAPS       \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, P010_10LE, YUY2 }")

# define GST_MFX_SUPPORTED_INPUT_FORMATS \
    "{ NV12, YV12, I420, YUY2, P010_10LE, BGRA, BGRx }"

# define GST_MFX_SUPPORTED_OUTPUT_FORMATS \
    "{ NV12, BGRA, P010_10LE, YUY2 }"
# endif // GST_CHECK_VERSION
# else
# define GST_MFX_MAKE_INPUT_SURFACE_CAPS        \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, YUY2 }")

# define GST_MFX_MAKE_OUTPUT_SURFACE_CAPS       \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, YUY2 }")

# define GST_MFX_SUPPORTED_INPUT_FORMATS \
    "{ NV12, YV12, I420, UYVY, YUY2, BGRA, BGRx }"

# define GST_MFX_SUPPORTED_OUTPUT_FORMATS \
    "{ NV12, BGRA, YUY2 }"
# endif // MSDK_CHECK_VERSION
#else
# define GST_MFX_MAKE_INPUT_SURFACE_CAPS        \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, P010_10LE, YUY2 }")

# define GST_MFX_MAKE_OUTPUT_SURFACE_CAPS       \
    GST_VIDEO_CAPS_MAKE_WITH_FEATURES           \
    (GST_CAPS_FEATURE_MEMORY_MFX_SURFACE, "{ NV12, BGRA, P010_10LE, YUY2, ENCODED }")

# define GST_MFX_SUPPORTED_INPUT_FORMATS \
    "{ NV12, YV12, I420, YUY2, P010_10LE, BGRA, BGRx }"

# define GST_MFX_SUPPORTED_OUTPUT_FORMATS \
    "{ NV12, BGRA, P010_10LE, YUY2 }"
#endif // WITH_LIBVA_BACKEND

gboolean
gst_mfx_ensure_aggregator (GstElement * element);

gboolean
gst_mfx_handle_context_query (GstQuery * query, GstMfxTaskAggregator * context);

GstCaps *
gst_mfx_video_format_new_template_caps (GstVideoFormat format);

GstCaps *
gst_mfx_video_format_new_template_caps_with_features (GstVideoFormat
    format, const gchar * features_string);

#ifdef HAVE_GST_GL_LIBS
gboolean
gst_mfx_check_gl_texture_sharing (GstElement * element,
    GstPad * pad, GstGLContext ** gl_context_ptr);
#endif

GstMfxCapsFeature
gst_mfx_find_preferred_caps_feature (GstPad * pad,
    gboolean use_10bpc, gboolean has_gl_texture_sharing,
    GstVideoFormat * out_format_ptr);

const gchar *
gst_mfx_caps_feature_to_string (GstMfxCapsFeature feature);

gboolean
gst_caps_has_mfx_surface (GstCaps * caps);

gboolean
gst_caps_has_gl_memory (GstCaps * caps);

gboolean
gst_mfx_query_peer_has_raw_caps (GstCaps * caps);

void
gst_video_info_change_format (GstVideoInfo * vip, GstVideoFormat format,
    guint width, guint height);

gboolean
gst_mfx_is_mfx_supported (mfxU16 * platform_code);

#endif /* GST_MFX_PLUGIN_UTIL_H */
