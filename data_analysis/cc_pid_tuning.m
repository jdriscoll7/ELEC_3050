% Pid controller tuning - Cohen Coon calculations/rules
dead_time = 0.01;
process_gain = 0.4394;
tau = 0.1889;
T = 1/100;

% Cohen-Coon equations.
Kp = (1.35/process_gain)*(0.185+(tau/dead_time)) / 2;
Ki = 2.5*dead_time*(tau + 0.185*dead_time)/(tau + 0.611*dead_time);
Kd = 0.37*dead_time*tau/(tau + 0.185*dead_time);


% Stuff to plug into C program.
A0 = (Kp + (Ki*T/2) + (Kd/T))*(2^20)
A1 = (Kp + (Kd/T) - (Ki*T/2) + (Kd/T))*(2^20)
A2 = (Kd/T)*(2^20)

