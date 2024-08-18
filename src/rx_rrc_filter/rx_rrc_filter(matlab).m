sps = 8; % samples per symbol

%
% Root raised cosine pulse filter
% https://www.michael-joost.de/rrcfilter.pdf
%
beta = 0.3; % bandwidth factor

ntaps = 8 * sps + 1;  % filter is 8 symbols in length
st = [-floor(ntaps/2):floor(ntaps/2)] / sps;  % symbol time
hpulse = 1/sqrt(sps) * (sin ((1-beta)*pi*st) + 4*beta*st.*cos((1+beta)*pi*st)) ./ (pi*st.*(1-(4*beta*st).^2));

% fix the removable singularities
hpulse(ceil(ntaps/2)) = 1/sqrt(sps) * (1 - beta + 4*beta/pi); % t = 0 singulatiry
sing_idx = find(abs(1-(4*beta*st).^2) < 0.000001);
for k = [1:length(sing_idx)]
    hpulse(sing_idx) = 1/sqrt(sps) * beta/sqrt(2) * ((1+2/pi)*sin(pi/(4*beta))+(1-2/pi)*cos(pi/(4*beta)));
    fprintf('Fixed the other removable singularities\n');
end

% normalize to 0 dB gain
hpulse = hpulse / sum(hpulse);


figure(1);
plot(st, hpulse, 'x-');
xlabel("Time (symbols)");
ylabel("Amplitude");
title("RRC Filter Taps");
grid on;