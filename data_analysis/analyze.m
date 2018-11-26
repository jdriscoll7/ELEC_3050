file_name = "test_data_0_to_100.csv";
input_value = 2.5;

data = csvread(file_name);
data = data(1:(length(data)-1));
t = (0:(length(data)-1)) / 100;

%% Impulse response estimation using frequency domain analysis.
dft_x = fft(input_value*[0 ones(1, length(data) - 1)]);
dft_y = fft(data);

test_input = 1.25*[0 ones(1, length(data) - 1)];
dft_test_input = fft(test_input);

figure(1)
title("Test response.");
freq_response = dft_y./dft_x;
plot((1:500)/100, abs(ifft(freq_response.*dft_test_input)))

figure(2)
title("Frequency response.");
freq_response = dft_y./dft_x;
plot(0.002/0.01:(0.002/0.01):(1/0.01), abs(freq_response))




%% Pole-zero plot of dft's.
close all;
figure(1)
zplane(dft_y, dft_x)
figure(2)
freqz(dft_y, dft_x)

%% Plant parameter estimation.

close all;

% Cubic spline interpolation on data - upsample by 100 times.
interp_t = (0:(100*length(data)-1)) / (100 * 100);
interp_data = spline(t, data, interp_t);


% Average the last half of data points of the data.
data_max = mean(interp_data((length(interp_data)-(length(interp_data)/2)):length(interp_data)));


% Determine the time constant tau.
[value, tau] = min(abs(interp_data - (0.6321*data_max)));

result = sprintf(['\n**********************\n', ...
                  '* Gain: %12.4f *\n', ...
                  '* Tau:  %12.4f *\n',  ...
                  '**********************\n'], data_max/input_value, (tau-1)/10000);
              
disp(result);


plot(interp_t, interp_data);