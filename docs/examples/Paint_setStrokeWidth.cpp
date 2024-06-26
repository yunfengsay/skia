// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Paint_setStrokeWidth, 256, 256, true, 0) {
void draw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setStrokeWidth(5);
    paint.setStrokeWidth(-1);
    SkDebugf("5 %c= paint.getStrokeWidth()\n", 5 == paint.getStrokeWidth() ? '=' : '!');
}
}  // END FIDDLE
