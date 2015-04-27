from Tkinter import *
#import serial
#import SerialSend
#from time import sleep





def doNothing():
    print("ok, I won't")
    return 0


def callStartCapture():
    comPort = port.get()
    baudrate = 115200 #make this an input from the gui
    startCapture(comPort, baudrate)
    return 0


def startCapture(port, baudrate):
    print('port = ' + port)
    ReadDataSize = 32 # make this an input from the gui
    q=0
    while(q!='exit'):
        choice = raw_input("read or write or exit")
        if(choice =="write"):
            string = 0
            write_Characteristics = serial.Serial(port, baudrate)
            while(string!='1'):
                string = raw_input('What would you like to send?') #edit this line to accept
                #input from matt's gui
                SerialSend.send(write_Characteristics, string)
            write_Characteristics.close()
        elif(choice == 'read'):
            read_Characteristics = serial.Serial(port, baudrate, timeout=None)
            fromSerial = 0
            while(fromSerial!='10      '):
                fromSerial = SerialSend.read(read_Characteristics, ReadDataSize)
                print 'from the serial port'+str(fromSerial)
            read_Characteristics.close()
        elif(choice == 'exit'):
            q=choice
        else:
            print 'not a valid choice, try again'
    print 'finished executing'
        #then send capture message over uart
    return 0


def connectToCom():
    print("connecting to com")
    #Put Jason's code here
    return 0       #needs to be changed depending on Jason's code


def stopCapture():
    print("stop capture")
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
connectButton = Button(toolbar, text="Connect to port", command = printPort)
connectButton.pack(side=LEFT, padx=2, pady=2)
startCaptureButton = Button(toolbar, text="Start capture", command = callStartCapture)
startCaptureButton.pack(side=LEFT, padx=2, pady=2)
stopCaptureButton = Button(toolbar, text="Stop capture", command = stopCapture)
stopCaptureButton.pack(side=LEFT, padx=2, pady=2)
toolbar.pack(side=TOP, fill=X)


#Status bar
status = Label(root, text="Preparing to do nothing", bd=1, relief=SUNKEN, anchor=W)
status.pack(side=BOTTOM, fill=X)

#Text input
mEntry = Entry(root,textvariable=port).pack(side=TOP)

#Text Output
ButtonText = 'Enter your port'
text = Label(text=ButtonText).pack()



root.mainloop()