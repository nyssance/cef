// Copyright (c) 2026 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "cef/libcef/browser/background_color_util.h"

#include "tests/gtest/include/gtest/gtest.h"

namespace {

using background_color_util::ResolveBackgroundColor;

constexpr bool kWindowed = false;
constexpr bool kWindowless = true;

constexpr cef_color_t kOpaqueRed = CefColorSetARGB(0xFF, 0xFF, 0x00, 0x00);
constexpr cef_color_t kTransparentRed = CefColorSetARGB(0x00, 0xFF, 0x00, 0x00);
constexpr cef_color_t kTranslucentRed = CefColorSetARGB(0x80, 0xFF, 0x00, 0x00);
constexpr cef_color_t kUnset = 0;

TEST(BackgroundColorUtilTest, WindowlessKeepsExistingBehavior) {
  for (const bool allow_transparency : {false, true}) {
    EXPECT_EQ(SK_ColorRED, ResolveBackgroundColor(kOpaqueRed, kWindowless,
                                                  allow_transparency));
    EXPECT_EQ(SK_ColorTRANSPARENT,
              ResolveBackgroundColor(kTransparentRed, kWindowless,
                                     allow_transparency));
    EXPECT_EQ(SK_ColorTRANSPARENT,
              ResolveBackgroundColor(kUnset, kWindowless, allow_transparency));
    // A partially transparent color is treated as opaque.
    EXPECT_EQ(SK_ColorRED, ResolveBackgroundColor(kTranslucentRed, kWindowless,
                                                  allow_transparency));
  }
}

TEST(BackgroundColorUtilTest, WindowedRequiresOpaqueByDefault) {
  EXPECT_EQ(SK_ColorRED, ResolveBackgroundColor(kOpaqueRed, kWindowed, false));
  EXPECT_EQ(std::nullopt,
            ResolveBackgroundColor(kTransparentRed, kWindowed, false));
  EXPECT_EQ(std::nullopt,
            ResolveBackgroundColor(kTranslucentRed, kWindowed, false));
  EXPECT_EQ(std::nullopt, ResolveBackgroundColor(kUnset, kWindowed, false));
}

TEST(BackgroundColorUtilTest, WindowedPreservesAlphaWhenAllowed) {
  EXPECT_EQ(SK_ColorRED, ResolveBackgroundColor(kOpaqueRed, kWindowed, true));
  EXPECT_EQ(SkColorSetARGB(0x00, 0xFF, 0x00, 0x00),
            ResolveBackgroundColor(kTransparentRed, kWindowed, true));
  EXPECT_EQ(SkColorSetARGB(0x80, 0xFF, 0x00, 0x00),
            ResolveBackgroundColor(kTranslucentRed, kWindowed, true));
  EXPECT_EQ(SK_ColorTRANSPARENT,
            ResolveBackgroundColor(kUnset, kWindowed, true));
}

}  // namespace
