diagnostic(off, derivative_uniformity);
diagnostic(off, chromium.unreachable_code);
struct FSOut {
  @location(0) sk_FragColor: vec4<f32>,
};
struct _GlobalUniforms {
  colorGreen: vec4<f32>,
  colorRed: vec4<f32>,
};
@binding(0) @group(0) var<uniform> _globalUniforms: _GlobalUniforms;
fn _skslMain(coords: vec2<f32>) -> vec4<f32> {
  {
    let inputVal: vec4<bool> = vec4<bool>(_globalUniforms.colorGreen);
    const expected: vec4<bool> = vec4<bool>(true, false, true, false);
    return select(_globalUniforms.colorRed, _globalUniforms.colorGreen, vec4<bool>(((((all((!inputVal.xy) == expected.xy) && all((!inputVal.xyz) == expected.xyz)) && all((!inputVal) == expected)) && all(vec2<bool>(true, false) == expected.xy)) && all(vec3<bool>(true, false, true) == expected.xyz)) && all(vec4<bool>(true, false, true, false) == expected)));
  }
}
@fragment fn main() -> FSOut {
  var _stageOut: FSOut;
  _stageOut.sk_FragColor = _skslMain(/*fragcoord*/ vec2<f32>());
  return _stageOut;
}
