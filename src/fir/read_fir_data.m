#!/usr/bin/env octave


% reading input samples from stdin, one line at a time
values = [];
while true
    try
        vec = sscanf(input('', 's'), '(%f, %f)');

        if length(vec) == 0
            break
        end

        % pulling out real and imaginary parts
        re = vec(1);
        im = vec(2);

        % appending new baseband sample
        values = [values, re + 1j*im];

    catch
        break
    end
end

% plotting
max_mag = max(abs(values));

figure()
subplot(2,1,1)
plot(real(values))
xlim([0, length(values) - 1])
ylim([-max_mag, max_mag])
ylabel('real')
grid

subplot(2,1,2)
h = plot(imag(values));
xlim([0, length(values) - 1])
ylim([-max_mag, max_mag])
ylabel('imag')
grid


waitfor(h)
