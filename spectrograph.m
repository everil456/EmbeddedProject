%Listening experiment

%setup
nbits = 16;         %Bits of Resolution
fs = 44000;         %Sampling Frequency
nchannels = 1;      %number of channels
f = linspace(-1*(fs/2),fs/2,length(mySpectrum)); %frequency range

%Create and audio recorder object
recObj = audiorecorder(fs,nbits,nchannels);

%Set up the measurement variables
power = [];
data1 = [];
data2 = [];
data3 = [];
data4 = [];
data5 = [];
data6 = [];
data7 = [];

%Start the Spectrograph (hit CTL-C to stop the spectrograph)
disp('Starting Spectrograph')

%Use an update loop to take the measurements
while(1)
    
% Record your voice for 0.1 seconds.
recordblocking(recObj, 0.1);


% Play back the recording.
% play(recObj);

% Store data in double-precision array.
myRecording = getaudiodata(recObj);

%find the spectrum of the recorded Sound
mySpectrum = fftshift(abs(fft(myRecording)));


%Update the display
data7 = data6;
data6 = data5;
data5 = data4;
data4 = data3;
data3 = data2;
data2 = data1;
data1 = myRecording(1332:end);
data = [data7;data6;data5;data4;data3;data2;data1];

power = [power,sum(myRecording.^2)];

% Plot the waveforms.
figure(1)
subplot(3,1,1)
plot(data)
title('Recorded Sound')

subplot(3,1,2)
plot(f,mySpectrum)
title('Spectrum in Hz')

subplot(3,1,3)
plot(power)
title('Recieved Power')
end