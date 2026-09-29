// Copyright (c) 2026 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "cef/libcef/browser/background_color_util.h"

namespace background_color_util {

std::optional<SkColor> ResolveBackgroundColor(cef_color_t cef_color,
                                              bool is_windowless,
                                              bool allow_transparency) {
  const auto alpha = CefColorGetA(cef_color);

  if (is_windowless) {
    // Windowless browser colors may be fully transparent.
    if (alpha == SK_AlphaTRANSPARENT) {
      return SK_ColorTRANSPARENT;
    }
  } else if (alpha != SK_AlphaOPAQUE) {
    // Windowed browser colors must be fully opaque unless transparency is
    // explicitly allowed, in which case the alpha component is preserved.
    if (!allow_transparency) {
      return std::nullopt;
    }
    return SkColorSetARGB(alpha, CefColorGetR(cef_color),
                          CefColorGetG(cef_color), CefColorGetB(cef_color));
  }

  // Ignore the alpha component.
  return SkColorSetRGB(CefColorGetR(cef_color), CefColorGetG(cef_color),
                       CefColorGetB(cef_color));
}

}  // namespace background_color_util
