##hi matt, this code is what you will copy into your gui code.
import serial
import SerialSend
from time import sleep

port = "COM1" #make this an input from the gui
baudrate = 115200 #make this an input from the gui
#timeout = None

ReadDataSize = 8 # make this an input from the gui
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
