from flask import Flask
from time import sleep
import serial


SERIALPORT = '/dev/cu.usbmodem1411'
BAUDRATE = 9600
READY_SYMBOL = 'R'
DELIMITER = '\n'
WR_BUF_TIME = 0.5

app = Flask(__name__)
ser = serial.Serial(SERIALPORT, BAUDRATE)


@app.route('/tune/<freq>')
def tune(freq):
    msg = ser.read()
    if (msg.decode('utf-8') == READY_SYMBOL):
        fin_b = (str(freq) + DELIMITER).encode()
        ser.write(fin_b)
        sleep(WR_BUF_TIME)
        fout_b = ser.readline()
        fout = fout_b.decode('utf-8')
        print("Set frequency to {}".format(fout))
        return "Now playing {}".format(fout)

    else:
        return 'Not ready'
