from flask import Flask, render_template, request
from serial import Serial
import sys

app = Flask(__name__)

SERIAL_PORT = sys.argv[1] if len(sys.argv) > 1 else 'COM3'
BAUD_RATE = 9600
serial_com = Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=3)


def ledOn():
    serial_com.write("A".encode())


def ledOff():
    serial_com.write("S".encode())


def readSerialData():
    return serial_com.readline().decode("utf-8")


@app.route("/", methods=['GET', 'POST'])
def index():
    temperature = readSerialData()
    if request.method == 'POST':
        if 'on' in request.form.to_dict():
            ledOn()
        if 'off' in request.form.to_dict():
            ledOff()

    return render_template('index.html', temp = temperature)

if __name__ == "__main__":
    app.run()
