file_name = "test_data_30_to_100.csv";
input_value = 2.5;

data = csvread(file_name);
data = data(1:(length(data)-1));
t = (0:(length(data)-1)) / 100;


% Cubic spline interpolation on data.
interp_t = (0:(100*length(data)-1)) / (100 * 100);
interp_data = spline(t, data, interp_t);

% Average the last 10 data points of the data.
data_max = mean(interp_data((length(interp_data)-(length(interp_data)/2)):length(interp_data)));


% Determine the time constant tau.
[value, tau] = min(abs(interp_data - (0.6321*data_max)));

result = sprintf(['\n**********************\n', ...
                  '* Gain: %12.4f *\n', ...
                  '* Tau:  %12.4f *\n',  ...
                  '**********************\n'], data_max/input_value, (tau-1)/10000);
              
disp(result);


plot(interp_t, interp_data);