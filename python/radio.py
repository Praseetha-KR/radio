from flask import Flask
from time import sleep
import serial

app = Flask(__name__)
app.config.from_pyfile('config.py')

try:
    ser = serial.Serial(app.config['SERIALPORT'], app.config['BAUDRATE'])
except:
    print('ERROR: could not open port {}'.format(app.config['SERIALPORT']))


@app.route('/stations/<loc>')
def stations(loc):
    try:
        loc_stations = app.config['STATIONS_LIST'][loc.upper()]
        loc_list = ''
        for k in loc_stations:
            loc_list += '<li><a href="/tune/{0}">{0}</a>: {1}</li>'.format(
                k, loc_stations[k]
            )
    except:
        loc_list = 'No stations listed'

    return '<h3>FM Stations List: {}</h3><ul>{}</ul>'.format(
        loc.upper(),
        loc_list
    )


@app.route('/tune/<freq>')
def tune(freq):
    msg = ser.read()
    if (msg.decode('utf-8') == app.config['READY_SYMBOL']):
        fin_b = (str(freq) + app.config['DELIMITER']).encode()
        ser.write(fin_b)
        sleep(app.config['WR_BUF_TIME'])
        fout_b = ser.readline()
        fout = fout_b.decode('utf-8')
        return 'Now playing {}'.format(fout)

    else:
        return 'Not ready'
