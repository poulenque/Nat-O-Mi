# generate wav file containing sine waves
# FB36 - 20120617
import math, wave, array
duration = 30 # seconds
freq = 440 # of cycles per second (Hz) (frequency of the sine waves)
volume = 10 # percent
data = array.array('h') # signed short integer (-32768 to 32767) data
sampleRate = 22050 # of samples per second (standard)
numChan = 1 # of channels (1: mono, 2: stereo)
dataSize = 2 # 2 bytes because of using signed short integers => bit depth = 16
numSamplesPerCyc = int(sampleRate / freq)
numSamples = sampleRate * duration

sampleReader = [line.strip() for line in open('test2.csv','r') if line.strip() and not line.startswith('#')]

for i in sampleReader:
    sample = 32767 * float(volume) / 100 #amplitude
    sample *= float(i)
    data.append(int(sample))

f = wave.open('Sample.wav', 'w')
f.setparams((numChan, dataSize, sampleRate, numSamples, "NONE", "Uncompressed"))
f.writeframes(data.tostring())
f.close()
