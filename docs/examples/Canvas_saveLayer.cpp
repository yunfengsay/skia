// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#include "tools/fiddle/examples.h"
REG_FIDDLE(Canvas_saveLayer, 256, 128, false, 0) {
#include "include/effects/SkImageFilters.h"

void draw(SkCanvas* canvas) {
    SkPaint paint, blur;
    blur.setImageFilter(SkImageFilters::Blur(3, 3, nullptr));
    canvas->saveLayer(nullptr, &blur);
    SkRect rect = { 25, 25, 50, 50};
    canvas->drawRect(rect, paint);
    canvas->translate(50, 50);
    paint.setColor(SK_ColorRED);
    canvas->drawRect(rect, paint);
    canvas->restore();
}
}  // END FIDDLE
