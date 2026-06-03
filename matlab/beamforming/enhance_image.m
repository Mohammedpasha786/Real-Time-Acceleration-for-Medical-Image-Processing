function out = enhance_image(img)
% Speckle reduction + adaptive histogram equalization
coder.gpu.kernelfun();

% Wiener filter for speckle reduction
img_filtered = wiener2(img, [5 5]);

% Adaptive histogram equalization
out = adapthisteq(img_filtered, 'ClipLimit', 0.02, 'Distribution', 'rayleigh');
end
