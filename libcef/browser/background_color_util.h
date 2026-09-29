// Copyright (c) 2026 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_BACKGROUND_COLOR_UTIL_H_
#define CEF_LIBCEF_BROWSER_BACKGROUND_COLOR_UTIL_H_
#pragma once

#include <optional>

#include "cef/include/internal/cef_types.h"
#include "third_party/skia/include/core/SkColor.h"

namespace background_color_util {

// Converts |cef_color| to the SkColor used as the browser background color, or
// returns std::nullopt if |cef_color| is not acceptable for this kind of
// browser.
//
// Windowless browsers accept a fully transparent color, which enables
// transparent painting; any other alpha value is ignored and the RGB components
// are used as an opaque color.
//
// Windowed browsers require a fully opaque color unless |allow_transparency| is
// true, in which case the alpha component is preserved. See the
// CefSettings.allow_transparency documentation.
std::optional<SkColor> ResolveBackgroundColor(cef_color_t cef_color,
                                              bool is_windowless,
                                              bool allow_transparency);

}  // namespace background_color_util

#endif  // CEF_LIBCEF_BROWSER_BACKGROUND_COLOR_UTIL_H_
