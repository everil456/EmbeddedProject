from Tkinter import *
import serial
import SerialSend
from time import sleep
import threading



read_Characteristics = serial.Serial("COM1", 115200, timeout =None)
read_Characteristics.close()
def doNothing():
    print("ok, I won't")
    return 0


def callStartCapture():

    stopCaptureButton.config(state=NORMAL)
    dataCapture = threading.Thread(name ='capture', target=realStartCapture)
    dataCapture.start()
    return 0


def realStartCapture():
    comPort = port.get()
    baudrate = bRate.get() #make this an input from the gui
    print 'baudrate = ' + baudrate
    if(baudrate == ""):
        baudrate = 115200
    startCapture(comPort, baudrate)
    return 0


def startCapture(port, baudrate):
    print('startCaptureButton status = ' + str(startCaptureButton["state"]))#for testing
    print('stopCaptureButton status = ' + str(stopCaptureButton["state"]))#for testing
    while(stopCaptureButton['state']!='normal'):
        stopCaptureButton.config(state=NORMAL)
        #print("waiting")
    startCaptureButton.config(state=DISABLED)
    print('port = ' + port)
    ReadDataSize = 800 # make this an input from the gui
    print('startCaptureButton status = ' + str(startCaptureButton["state"]))#for testing
##    write_Characteristics = serial.Serial(port, baudrate)
##    SerialSend.send(write_Characteristics, "GIVE ME DATA OUT OF WHILE LOOP")
##    write_Characteristics.close()
    while(startCaptureButton['state'] =='disabled'):
        write_Characteristics = serial.Serial(port, baudrate)
        SerialSend.send(write_Characteristics, "g")
        write_Characteristics.close()
        read_Characteristics = serial.Serial(port, baudrate, timeout=None)
        fromSerial = SerialSend.read(read_Characteristics, ReadDataSize)
        print 'from the serial port'+str(fromSerial)
        read_Characteristics.close()
    print 'finished executing'
        #then send capture message over uart
    return 0


def connectToCom():
    print("connecting to com")
    startCaptureButton.config(state=NORMAL)
    stopCaptureButton.config(state=NORMAL)
    #Put Jason's code here
    return 0       #needs to be changed depending on Jason's code


def stopCapture():
    print("stop capture")
    startCaptureButton.config(state=NORMAL)
    #Put Jason's code here
    return 0       #needs to be changed depending on Jason's code


def printPort():
    mtext = port.get()
    comport = connectToCom()
    print("Com = " + mtext)
    return mtext


root = Tk()
root.geometry('1200x600')
root.title('Sonic Locator')


port = StringVar()
bRate = StringVar()





# Menu Stuff
mainMenu = Menu(root)
root.config(menu=mainMenu)

subMenu = Menu(mainMenu)
mainMenu.add_cascade(label="File", menu=subMenu)
subMenu.add_command(label="New Project", command=doNothing)
subMenu.add_command(label="New", command=doNothing)
subMenu.add_separator()
subMenu.add_command(label="Exit", command=root.quit)

editMenu = Menu(mainMenu)
mainMenu.add_cascade(label="Edit", menu=editMenu)
editMenu.add_command(label="Redo", command=doNothing)

#Toolbar Stuff
toolbar = Frame(root, bg="grey")
connectButton = Button(toolbar, text="Enter COM port and Baudrate", command = printPort)
connectButton.pack(side=LEFT, padx=2, pady=2)
startCaptureButton = Button(toolbar, text="Start capture", command = callStartCapture)
startCaptureButton.config(state=DISABLED)
startCaptureButton.pack(side=LEFT, padx=2, pady=2)
stopCaptureButton = Button(toolbar, text="Stop capture", command = stopCapture)
stopCaptureButton.config(state=DISABLED)
stopCaptureButton.pack(side=LEFT, padx=2, pady=2)
toolbar.pack(side=TOP, fill=X)


#Status bar
status = Label(root, text="Preparing to do nothing", bd=1, relief=SUNKEN, anchor=W)
status.pack(side=BOTTOM, fill=X)

#Text input
mEntry = Entry(root,textvariable=port).pack(side=LEFT)
bRateEntry = Entry(root,textvariable=bRate).pack(side=RIGHT)

#Text Output
ButtonText = 'Enter your port'
text = Label(text=ButtonText).pack(side = LEFT)
BRTextBox = 'Enter your baudrate'
text = Label(text=BRTextBox).pack(side = RIGHT)




root.mainloop()
