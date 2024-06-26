// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Point_negate, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    SkPoint test[] = { {0.f, -0.f}, {-1, -2},
                       { SK_ScalarInfinity, SK_ScalarNegativeInfinity },
                       { SK_ScalarNaN, -SK_ScalarNaN } };
    for (const SkPoint& pt : test) {
        SkPoint negPt = pt;
        negPt.negate();
        SkDebugf("pt: %g, %g  negate: %g, %g\n", pt.fX, pt.fY, negPt.fX, negPt.fY);
    }
}
}  // END FIDDLE
