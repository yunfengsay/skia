#ifndef OPTIMIZED_DRAW_H
#define OPTIMIZED_DRAW_H

#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"
#include "include/core/SkRRect.h"
#include "include/core/SkImage.h"
#include "modules/skparagraph/include/Paragraph.h"
#include <vector>
#include <memory>

namespace skia {
namespace {

enum class ElementType {
    Rect,
    Path,
    Image,
    Text,
    Group
};

struct ElementProps {
    SkRect rect;
    SkScalar cornerRadius = 0;
    SkPaint paint;
    SkPath path;
    sk_sp<SkImage> image;
    bool resample = false;
    std::unique_ptr<skia::textlayout::Paragraph> paragraph;
    SkMatrix transform;
    SkScalar opacity = 1.0f;
    sk_sp<SkImageFilter> imageFilter;
    sk_sp<SkColorFilter> colorFilter;
    std::unique_ptr<SkClipOp> clipOp;
    SkPath clipPath;
};

struct Element {
    ElementType type;
    ElementProps props;
    std::vector<std::unique_ptr<Element>> children;

    Element(ElementType t) : type(t) {}
};

void OptimizedDraw(const Element& element, SkCanvas* canvas);

// Helper function to create Element from JavaScript object
std::unique_ptr<Element> CreateElementFromJSObject(const emscripten::val& jsObject);

} // namespace
} // namespace skia

#endif // OPTIMIZED_DRAW_H