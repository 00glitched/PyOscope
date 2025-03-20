import serial.tools.list_ports
import time
import sys

#print(list(serial.tools.list_ports.comports()))




#s={}

allPorts = serial.tools.list_ports.comports()

def availablePorts(portList):
    portAvailable=[]
    for port, desc, hwid in sorted(portList):
        if hwid!="n/a":
            portAvailable.append("{}: {} [{}]".format(port, desc, hwid))               
    return portAvailable

def serialBegin(port,rate=9600):
    s = serial.Serial(port, rate)

def serialWrite(string):
    s.write(string)
        
def serialRead():
    return s.read()

def serialEnd():
    s.close()

if __name__ == '__main__':
    
    portsToConnect = availablePorts(allPorts)
    if len(portsToConnect) > 0:
        mySerialPort = str(portsToConnect[0])
        myBaudrate = 9600
        myMsg = "Hello World"
        
        print("serialPortList:")
        print(portsToConnect)
        print("serialPort: "+mySerialPort)
        print("baudRate: "+str(myBaudrate))
        print("message: "+myMsg) 
    else:
        print("Unavailable ports")   
    #serialBegin(mySerialPort,myBaudrate)
    #serialWrite(myMsg)
    #serialEnd()
