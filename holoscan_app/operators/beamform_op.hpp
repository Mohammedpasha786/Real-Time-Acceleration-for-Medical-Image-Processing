#pragma once
#include <holoscan/holoscan.hpp>

namespace ops {

class BeamformOp : public holoscan::Operator {
public:
  HOLOSCAN_OPERATOR_FORWARD_ARGS(BeamformOp)
  BeamformOp() = default;

  void setup(holoscan::OperatorSpec& spec) override;
  void compute(holoscan::InputContext& in,
               holoscan::OutputContext& out,
               holoscan::ExecutionContext& ctx) override;
};

} // namespace ops
