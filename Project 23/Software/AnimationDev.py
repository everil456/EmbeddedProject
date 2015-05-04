import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation
import serial
import SerialSend

def hex2dec(hexstr):
    Data_array = []
    temp = ''

    for i in range(len(hexstr)):
        if hexstr[i] == "*":
            temp += '0'
        else:
            temp+= hexstr[i]

    hexstr = temp
    
    for i in range(0, len(hexstr)):
        Data_array.append(int(hexstr[i:i+8],16))
    print Data_array
    return Data_array
# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim = (0,240), ylim = (-500,500))
line, = ax.plot([], [], lw=2)

# initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    return line,

# animation function.  This is called sequentially
def animate(i):
    
    
    ReadDataSize = 240 # make this an input from the gui    
    
    write_Characteristics = serial.Serial("COM12", "115200")
    SerialSend.send(write_Characteristics, "g")
    write_Characteristics.close()
    read_Characteristics = serial.Serial("COM12", "115200", timeout=.5)
    fromSerial = SerialSend.read(read_Characteristics, ReadDataSize)
    print 'from the serial port'+str(fromSerial)
    read_Characteristics.close()
    serialData = hex2dec(fromSerial)
    
    serialData = np.array(serialData)
    serialData = serialData/10000000
##    serialDataFFT = np.fft.fft(serialData)
    print serialData
    #y = np.random.rand(200)
    x = np.arange(len(serialData))    
    line.set_data(x, serialData)
    return line,

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=200, interval=50, blit=True)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html

##anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
