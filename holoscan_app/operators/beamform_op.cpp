#include "beamform_op.hpp"
#include "us_beamform.h"   // MATLAB GPU Coder generated header

namespace ops {

void BeamformOp::setup(holoscan::OperatorSpec& spec) {
  spec.input<holoscan::gxf::Entity>("rf_in");
  spec.output<holoscan::gxf::Entity>("image_out");
}

void BeamformOp::compute(holoscan::InputContext& in,
                          holoscan::OutputContext& out,
                          holoscan::ExecutionContext& ctx) {
  auto rf_entity = in.receive<holoscan::gxf::Entity>("rf_in").value();
  // Extract tensor, call MATLAB-generated CUDA function
  // us_beamform(rf_ptr, fs, c, pitch, focus_depth, output_ptr);
  // Pack result and emit
  out.emit(rf_entity, "image_out");  // replace with processed entity
}

} // namespace ops
