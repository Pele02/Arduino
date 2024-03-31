from flask import Flask, render_template, request
from serial import Serial

serial_com = Serial(port='COM3', baudrate=9600, timeout=0.1)

app = Flask(__name__)


def ledOn():
    serial_com.write(str('on').encode())


def ledOff():
    serial_com.write(str('off').encode())


def disconnect():
    serial_com.close()


@app.route("/", methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'on' in request.form.to_dict():
            ledOn()
        if 'off' in request.form.to_dict():
            ledOff()
        if 'dis' in request.form.to_dict():
            disconnect()

    return render_template('index.html')


if __name__ == "__main__":
    app.run()
