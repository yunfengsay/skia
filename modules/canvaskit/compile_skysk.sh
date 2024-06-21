#!/bin/bash
set -ex

BASE_DIR=`cd $(dirname ${BASH_SOURCE[0]}) && pwd`
pushd $BASE_DIR/../..
./bin/fetch-gn

IS_OFFICIAL_BUILD="true"
IS_DEBUG="false"
FORCE_TRACING="false"
PROFILE_BUILD="false"
if [[ $@ != *force_tracing* ]] ; then
  FORCE_TRACING="true"
fi

if [[ $@ == *debug_build* ]]; then
  echo "Building a Debug build"
  IS_DEBUG="true"
  IS_OFFICIAL_BUILD="false"
  BUILD_DIR=${BUILD_DIR:="out/canvaskit_wasm_debug"}
elif [[ $@ == *profiling* ]]; then
  echo "Building a build for profiling"
  PROFILE_BUILD="true"
  BUILD_DIR=${BUILD_DIR:="out/canvaskit_wasm_profile"}
else
  BUILD_DIR=${BUILD_DIR:="out/canvaskit_wasm"}
fi

mkdir -p $BUILD_DIR
rm -f $BUILD_DIR/*.a

ENABLE_GANESH="true"
ENABLE_GRAPHITE="true"
ENABLE_WEBGL="false"
ENABLE_WEBGPU="true"

SERIALIZE_SKP="false"
DESERIALIZE_EFFECTS="false"
ENABLE_SKOTTIE="false"
INCLUDE_VIEWER="false"
USE_EXPAT="false"
ENABLE_PATHOPS="false"
ENABLE_MATRIX="false"
ENABLE_CANVAS="true"
GN_FONT="skia_enable_fontmgr_custom_directory=false skia_enable_fontmgr_custom_embedded=false skia_enable_fontmgr_custom_empty=false"
WOFF2_FONT="skia_use_freetype_woff2=false"
ENABLE_FONT="true"
ENABLE_EMBEDDED_FONT="true"
ENABLE_ALIAS_FONT="true"
LEGACY_DRAW_VERTICES="false"
DEBUGGER_ENABLED="false"
GN_SHAPER="skia_use_icu=false skia_use_harfbuzz=false"
ENABLE_PARAGRAPH="false"
DO_DECODE="true"
ENCODE_JPEG="true"
ENCODE_PNG="true"
ENCODE_WEBP="true"
NO_ENCODE_JPEG="false"
NO_ENCODE_PNG="false"
NO_ENCODE_WEBP="false"

./bin/fetch-ninja
NINJA=third_party/ninja/ninja

echo "Compiling"

./bin/gn gen ${BUILD_DIR} \
  --args="is_debug=${IS_DEBUG} \
  is_official_build=${IS_OFFICIAL_BUILD} \
  is_component_build=false \
  is_trivial_abi=true \
  werror=true \
  target_cpu=\"wasm\" \
  skia_use_angle=false \
  skia_use_dng_sdk=false \
  skia_use_dawn=${ENABLE_WEBGPU} \
  skia_use_webgl=${ENABLE_WEBGL} \
  skia_use_webgpu=${ENABLE_WEBGPU} \
  skia_use_expat=${USE_EXPAT} \
  skia_use_fontconfig=false \
  skia_use_freetype=true \
  skia_use_libheif=false \
  skia_use_libjpeg_turbo_decode=${DO_DECODE} \
  skia_use_libjpeg_turbo_encode=${ENCODE_JPEG} \
  skia_use_no_jpeg_encode=${NO_ENCODE_JPEG} \
  skia_use_libpng_decode=${DO_DECODE} \
  skia_use_libpng_encode=${ENCODE_PNG} \
  skia_use_no_png_encode=${NO_ENCODE_PNG} \
  skia_use_libwebp_decode=${DO_DECODE} \
  skia_use_libwebp_encode=${ENCODE_WEBP} \
  skia_use_no_webp_encode=${NO_ENCODE_WEBP} \
  skia_use_lua=false \
  skia_use_piex=false \
  skia_use_system_freetype2=false \
  skia_use_system_libjpeg_turbo=false \
  skia_use_system_libpng=false \
  skia_use_system_libwebp=false \
  skia_use_system_zlib=false\
  skia_use_vulkan=false \
  skia_use_wuffs=true \
  skia_use_zlib=true \
  skia_enable_ganesh=${ENABLE_GANESH} \
  skia_enable_graphite=${ENABLE_GRAPHITE} \
  skia_build_for_debugger=${DEBUGGER_ENABLED} \
  skia_enable_skottie=${ENABLE_SKOTTIE} \
  ${GN_SHAPER} \
  ${GN_FONT} \
  ${WOFF2_FONT} \
  skia_enable_skshaper=true \
  skia_enable_skparagraph=${ENABLE_PARAGRAPH} \
  skia_enable_pdf=false \
  skia_canvaskit_enable_rt_shader=true \
  skia_canvaskit_force_tracing=${FORCE_TRACING} \
  skia_canvaskit_profile_build=${PROFILE_BUILD} \
  skia_canvaskit_enable_skp_serialization=${SERIALIZE_SKP} \
  skia_canvaskit_enable_effects_deserialization=${DESERIALIZE_EFFECTS} \
  skia_canvaskit_include_viewer=${INCLUDE_VIEWER} \
  skia_canvaskit_enable_pathops=${ENABLE_PATHOPS} \
  skia_canvaskit_enable_matrix_helper=${ENABLE_MATRIX} \
  skia_canvaskit_enable_canvas_bindings=${ENABLE_CANVAS} \
  skia_canvaskit_enable_font=${ENABLE_FONT} \
  skia_canvaskit_enable_embedded_font=${ENABLE_EMBEDDED_FONT} \
  skia_canvaskit_enable_alias_font=${ENABLE_ALIAS_FONT} \
  skia_canvaskit_legacy_draw_vertices_blend_mode=${LEGACY_DRAW_VERTICES} \
  skia_canvaskit_enable_debugger=${DEBUGGER_ENABLED} \
  skia_canvaskit_enable_paragraph=${ENABLE_PARAGRAPH} \
  skia_canvaskit_enable_webgl=${ENABLE_WEBGL} \
  skia_canvaskit_enable_webgpu=${ENABLE_WEBGPU}"

${NINJA} -C ${BUILD_DIR} canvaskit.js
