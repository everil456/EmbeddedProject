##
import serial
def send(ser, data):
    #ser.open()
    x = ser.write(data)
    print 'Message Sent'
    

def read(ser, ReadDataSize):
##    ser = serial.Serial(port, baudrate, timeout = timeout_option)#this isnt
##    #working right now
    
    x = ser.read(ReadDataSize)
    return x
