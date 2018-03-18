/*
 *  Copyright (C) 2010-2011 Splitted-Desktop Systems
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@splitted-desktop.com>
 *  Copyright (C) 2011-2013 Intel Corporation
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@intel.com>
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

#ifndef GST_MFX_DISPLAY_PRIV_H
#define GST_MFX_DISPLAY_PRIV_H

#include "gstmfxdisplay.h"

G_BEGIN_DECLS

#define GST_MFX_DISPLAY_CLASS(klass) \
    ((GstMfxDisplayClass *)(klass))
#define GST_MFX_DISPLAY_GET_CLASS(obj) \
    GST_MFX_DISPLAY_CLASS(GST_OBJECT_GET_CLASS (obj))
#define GST_MFX_DISPLAY_GET_PRIVATE(obj) \
    (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GST_TYPE_MFX_DISPLAY, \
    GstMfxDisplayPrivate))

typedef struct _GstMfxDisplayPrivate GstMfxDisplayPrivate;
typedef struct _GstMfxDisplayClass GstMfxDisplayClass;

typedef gboolean (*GstMfxDisplayOpenFunc) (GstMfxDisplay * display,
    const gchar * name);
typedef void (*GstMfxDisplayGetSizeFunc) (GstMfxDisplay * display,
    guint * pwidth, guint * pheight);
typedef void (*GstMfxDisplayGetSizeMFunc) (GstMfxDisplay * display,
    guint * pwidth, guint * pheight);

/**
* GST_MFX_DISPLAY_GET_CLASS_TYPE:
* @display: a #GstMfxDisplay
*
* Returns the #display class type
* This is an internal macro that does not do any run-time type check.
*/
#define GST_MFX_DISPLAY_GET_CLASS_TYPE(display) \
    (GST_MFX_DISPLAY_GET_CLASS (display)->display_type)

/**
* GST_MFX_DISPLAY_HANDLE:
* @display: a #GstMfxDisplay
*
* Macro that evaluates to the native display of @display.
* This is an internal macro that does not do any run-time type check.
*/
#define GST_MFX_DISPLAY_HANDLE(display) \
    (GST_MFX_DISPLAY_GET_PRIVATE (display)->native_display)


struct _GstMfxDisplayPrivate
{
  GRecMutex mutex;
  GstMfxDisplayType display_type;
  int display_fd;
  VADisplay va_display;
  gpointer native_display;
  guint width;
  guint height;
  guint width_mm;
  guint height_mm;
  guint par_n;
  guint par_d;
};

/**
 * GstMfxDisplayClass:
 * @open_display: virtual function to open a display
 * @close_display: virtual function to close a display
 * @get_size: virtual function to retrieve the display dimensions, in pixels
 * @get_size_mm: virtual function to retrieve the display dimensions, in millimeters
 * @create_window: (optional) virtual function to create a window
 *
 * Base class for VA displays.
 */
struct _GstMfxDisplayClass
{
  /*< private > */
  GstObjectClass parent_class;

  /*< protected > */
  guint display_type;

  /*< public > */
  GstMfxDisplayOpenFunc open_display;
  GstMfxDisplayGetSizeFunc get_size;
  GstMfxDisplayGetSizeMFunc get_size_mm;
};

GstMfxDisplay *
gst_mfx_display_new_internal (GstMfxDisplay * display, gpointer init_value);

G_END_DECLS
#endif /* GST_MFX_DISPLAY_PRIV_H */
