#include <holoscan/holoscan.hpp>
#include "operators/data_source_op.hpp"
#include "operators/beamform_op.hpp"
#include "operators/enhance_op.hpp"
#include "operators/inference_op.hpp"
#include <holoscan/operators/holoviz/holoviz.hpp>

class MedicalImagingApp : public holoscan::Application {
public:
  void compose() override {
    using namespace holoscan;

    auto source    = make_operator<ops::DataSourceOp>("source",
                       Arg("data_path", std::string("../data/sample_rf_data.mat")));
    auto beamform  = make_operator<ops::BeamformOp>("beamform");
    auto enhance   = make_operator<ops::EnhanceOp>("enhance");
    auto inference = make_operator<ops::InferenceOp>("inference",
                       Arg("model_path", std::string("../models/lesion_detector.onnx")));
    auto viz       = make_operator<ops::HolovizOp>("viz",
                       Arg("width", 1280u), Arg("height", 720u));

    // Pipeline: source → beamform → enhance → inference → viz
    add_flow(source,    beamform,  {{"rf_out", "rf_in"}});
    add_flow(beamform,  enhance,   {{"image_out", "image_in"}});
    add_flow(enhance,   inference, {{"enhanced_out", "image_in"}});
    add_flow(inference, viz,       {{"output", "receivers"}});
  }
};

int main() {
  auto app = holoscan::make_application<MedicalImagingApp>();
  app->run();
  return 0;
}
