function img = us_beamform(rf_data, fs, c, pitch, focus_depth)
% Delay-and-Sum beamformer
% rf_data: [samples x elements], fs: sampling freq, c: speed of sound
% pitch: element pitch (m), focus_depth: focal depth (m)

coder.gpu.kernelfun();   % GPU Coder directive

[N, M] = size(rf_data);
img = zeros(N, M, 'like', rf_data);

for i = 1:M
    x_elem = (i - M/2) * pitch;
    for n = 1:N
        z = (n / fs) * c / 2;
        for j = 1:M
            x_j = (j - M/2) * pitch;
            delay = sqrt((x_elem - x_j)^2 + z^2) / c;
            sample_idx = round(delay * fs);
            if sample_idx >= 1 && sample_idx <= N
                img(n, i) = img(n, i) + rf_data(sample_idx, j);
            end
        end
    end
end
img = abs(img);
end
