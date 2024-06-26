// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Region_quickReject_2, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    SkRegion region({1, 2, 3, 4});
    SkRegion test;
    SkIRect rects[] = {{4, 2, 5, 3}, {7, 2, 8, 3}};
    test.setRects(rects, std::size(rects));
    SkDebugf("quickReject 1: %s\n", region.quickReject(test) ? "true" : "false");
    region.op({1, 4, 3, 6}, SkRegion::kUnion_Op);
    SkDebugf("quickReject 2: %s\n", region.quickReject(test) ? "true" : "false");
    region.op({4, 7, 5, 8}, SkRegion::kUnion_Op);
    SkDebugf("quickReject 3: %s\n", region.quickReject(test) ? "true" : "false");
}
}  // END FIDDLE
