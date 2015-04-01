"""PyAudio example: Record a few seconds of audio and save to a WAVE file."""

import pyaudio
import wave

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
RECORD_SECONDS = 5
WAVE_OUTPUT_FILENAME = "output.wav"

p = pyaudio.PyAudio()

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

print("* recording")

frames = []

for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(data)

print("* done recording")

stream.stop_stream()
stream.close()
p.terminate()

wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
wf.setnchannels(CHANNELS)
wf.setsampwidth(p.get_sample_size(FORMAT))
wf.setframerate(RATE)


wr = wave.open(WAVE_OUTPUT_FILENAME, 'rb')

fs = wf.getframerate()
bytes_per_sample = wf.getsampwidth()
bits_per_sample  = bytes_per_sample * 8
dtype = 'int{0}'.format(bits_per_sample)
channels = wf.getnchannels()
wr.writeframes(b''.join(frames))
wr.close()


audio = np.fromstring(wr.readframes(int(duration*fs*bytes_per_sample/channels)), dtype=dtype)
audio.shape = (audio.shape[0]/channels, channels)

print audio
