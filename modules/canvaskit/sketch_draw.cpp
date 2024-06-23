#include "sketch_draw.h"
#include <emscripten/bind.h>

namespace skia {
namespace {

void DrawRect(const ElementProps& props, SkCanvas* canvas) {
    if (props.cornerRadius > 0) {
        SkRRect rrect;
        rrect.setRectXY(props.rect, props.cornerRadius, props.cornerRadius);
        canvas->drawRRect(rrect, props.paint);
    } else {
        canvas->drawRect(props.rect, props.paint);
    }
}

void DrawPath(const ElementProps& props, SkCanvas* canvas) {
    canvas->drawPath(props.path, props.paint);
}

void DrawImage(const ElementProps& props, SkCanvas* canvas) {
    SkRect src = SkRect::MakeWH(props.image->width(), props.image->height());
    if (props.resample) {
        // Note: This is a simplification. You might want to implement cubic resampling
        SkSamplingOptions sampling(SkFilterMode::kLinear, SkMipmapMode::kLinear);
        canvas->drawImageRect(props.image, src, props.rect, sampling, &props.paint);
    } else {
        canvas->drawImageRect(props.image, src, props.rect, SkSamplingOptions(), &props.paint);
    }
}

void DrawText(const ElementProps& props, SkCanvas* canvas) {
    if (props.paragraph) {
        props.paragraph->paint(canvas, props.rect.fLeft, props.rect.fTop);
    }
}

void DrawGroup(const Element& element, SkCanvas* canvas) {
    const auto& props = element.props;
    SkAutoCanvasRestore autoRestore(canvas, true);

    if (props.clipOp) {
        canvas->clipPath(props.clipPath, *props.clipOp);
    }

    canvas->concat(props.transform);

    bool needsLayer = props.opacity < 1.0f || props.imageFilter || props.colorFilter;
    if (needsLayer) {
        SkPaint layerPaint;
        layerPaint.setAlphaf(props.opacity);
        if (props.imageFilter) {
            layerPaint.setImageFilter(props.imageFilter);
        }
        if (props.colorFilter) {
            layerPaint.setColorFilter(props.colorFilter);
        }
        canvas->saveLayer(&props.rect, &layerPaint);
    }

    for (const auto& child : element.children) {
        OptimizedDraw(*child, canvas);
    }

    if (needsLayer) {
        canvas->restore();
    }
}

void OptimizedDraw(const Element& element, SkCanvas* canvas) {
    switch (element.type) {
        case ElementType::Rect:
            DrawRect(element.props, canvas);
            break;
        case ElementType::Path:
            DrawPath(element.props, canvas);
            break;
        case ElementType::Image:
            DrawImage(element.props, canvas);
            break;
        case ElementType::Text:
            DrawText(element.props, canvas);
            break;
        case ElementType::Group:
            DrawGroup(element, canvas);
            break;
    }
}

std::unique_ptr<Element> CreateElementFromJSObject(const emscripten::val& jsObject) {
    ElementType type = static_cast<ElementType>(jsObject["type"].as<int>());
    auto element = std::make_unique<Element>(type);

    // Parse properties from jsObject and set them in element->props
    // This is a simplified example, you'll need to handle all properties
    element->props.rect = SkRect::MakeXYWH(
        jsObject["rect"]["x"].as<float>(),
        jsObject["rect"]["y"].as<float>(),
        jsObject["rect"]["width"].as<float>(),
        jsObject["rect"]["height"].as<float>()
    );

    // Handle other properties...

    if (jsObject["children"].isArray()) {
        auto children = jsObject["children"].as<emscripten::val>();
        for (int i = 0; i < children["length"].as<int>(); ++i) {
            element->children.push_back(CreateElementFromJSObject(children[i]));
        }
    }

    return element;
}

// Wrapper function for JavaScript
void OptimizedDrawWrapper(const emscripten::val& jsElement, SkCanvas* canvas) {
    auto element = CreateElementFromJSObject(jsElement);
    OptimizedDraw(*element, canvas);
}

EMSCRIPTEN_BINDINGS(optimized_draw) {
    emscripten::function("optimizedDraw", &OptimizedDrawWrapper);
}

} // namespace
} // namespace skia