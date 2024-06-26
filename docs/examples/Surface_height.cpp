// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Surface_height, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    const int width = 37;
    const int height = 1000;
    auto surf = SkSurfaces::Null(width, height);
    auto nullCanvas = surf->getCanvas();
    SkDebugf("surface height=%d  canvas height=%d\n", surf->height(),
             nullCanvas->getBaseLayerSize().fHeight);
}
}  // END FIDDLE
