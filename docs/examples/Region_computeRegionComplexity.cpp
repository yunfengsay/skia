// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Region_computeRegionComplexity, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    auto debugster = [](const char* label, const SkRegion& region) -> void {
                SkDebugf("%s: region complexity %d\n", label, region.computeRegionComplexity());
    };
    SkRegion region;
    debugster("initial", region);
    region.setRect({1, 2, 3, 4});
    debugster("set rect", region);
    region.op({2, 3, 4, 5}, SkRegion::kUnion_Op);
    debugster("op rect", region);
}
}  // END FIDDLE
