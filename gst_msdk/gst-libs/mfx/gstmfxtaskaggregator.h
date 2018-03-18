/*
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

#ifndef GST_MFX_TASK_AGGREGATOR_H
#define GST_MFX_TASK_AGGREGATOR_H

#include "gstmfxtask.h"
#include "gstmfxcontext.h"

#include <mfxvideo.h>

G_BEGIN_DECLS

#define GST_TYPE_MFX_TASK_AGGREGATOR (gst_mfx_task_aggregator_get_type ())
G_DECLARE_FINAL_TYPE (GstMfxTaskAggregator, gst_mfx_task_aggregator, GST_MFX,
    TASK_AGGREGATOR, GstObject)

GstMfxTaskAggregator *
gst_mfx_task_aggregator_new (void);

GstMfxTaskAggregator *
gst_mfx_task_aggregator_ref (GstMfxTaskAggregator * aggregator);

void
gst_mfx_task_aggregator_unref (GstMfxTaskAggregator * aggregator);

void
gst_mfx_task_aggregator_replace (GstMfxTaskAggregator ** old_aggregator_ptr,
    GstMfxTaskAggregator * new_aggregator);

GstMfxTask *
gst_mfx_task_aggregator_get_current_task (GstMfxTaskAggregator * aggregator);

void
gst_mfx_task_aggregator_set_current_task (GstMfxTaskAggregator * aggregator,
  GstMfxTask * task);

GstMfxTask *
gst_mfx_task_aggregator_get_last_task (GstMfxTaskAggregator * aggregator);

void
gst_mfx_task_aggregator_add_task (GstMfxTaskAggregator * aggregator,
  GstMfxTask * task);

GstMfxContext *
gst_mfx_task_aggregator_get_context (GstMfxTaskAggregator * aggregator);

mfxSession
gst_mfx_task_aggregator_init_session_context (GstMfxTaskAggregator * aggregator,
    gboolean * is_joined);

void
gst_mfx_task_aggregator_remove_task (GstMfxTaskAggregator * aggregator,
    GstMfxTask * task);

#if MSDK_CHECK_VERSION(1,19)
mfxU16
gst_mfx_task_aggregator_get_platform (GstMfxTaskAggregator * aggregator);
#endif

G_END_DECLS
#endif /* GST_MFX_TASK_AGGREGATOR_H */
