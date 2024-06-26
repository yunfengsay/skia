// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Surface_props, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    const char* names[] = { "Unknown", "RGB_H", "BGR_H", "RGB_V", "BGR_V" };
    sk_sp<SkSurface> surf(SkSurfaces::Raster(SkImageInfo::MakeN32Premul(64, 64)));
    SkDebugf("surf.props(): k%s_SkPixelGeometry\n", names[surf->props().pixelGeometry()]);
}
}  // END FIDDLE
