from flask import Flask, render_template, request, jsonify
from serial import Serial
import sys

app = Flask(__name__)
LED_STATUS = None
MESSAGES = []
SERIAL_PORT = sys.argv[1] if len(sys.argv) > 1 else 'COM3'
BAUD_RATE = 9600
serial_com = Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=3)


def ledOn():
   serial_com.write("A".encode())


def ledOff():
   serial_com.write("S".encode())


def readSerialData():
   return serial_com.readline().decode("utf-8")

def saveMessage(message):
    serial_com.write(("M" + message + "\n").encode())  #Trimite mesaj la Arduino


@app.route("/", methods=['GET', 'POST'])
def index():
    global LED_STATUS
    temperature = readSerialData()
    if request.method == 'POST':
        if 'on' in request.form.to_dict():
            ledOn()
            LED_STATUS = "ON"
        if 'off' in request.form.to_dict():
            ledOff()
            LED_STATUS = "OFF"
        if 'message' in request.form:
            message = request.form['message']
            MESSAGES.append(message)
    return render_template('index.html', temp=temperature, led_status=LED_STATUS, messages=MESSAGES)


@app.route("/save_message", methods=['POST'])
def save_message():
    message = request.json.get('message')
    return jsonify(success=True)

if __name__ == "__main__":
    app.run()
