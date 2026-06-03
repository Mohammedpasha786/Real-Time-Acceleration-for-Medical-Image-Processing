FROM nvcr.io/nvidia/holoscan:1.0-dgpu

WORKDIR /workspace

RUN apt-get update && apt-get install -y \
    cmake build-essential libopencv-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . /workspace/medical-imaging-pipeline
WORKDIR /workspace/medical-imaging-pipeline/holoscan_app

RUN mkdir build && cd build && \
    cmake -DBUILD_BEAMFORM=ON -DBUILD_ENHANCE=ON .. && \
    make -j$(nproc)

CMD ["./build/medical_pipeline"]
