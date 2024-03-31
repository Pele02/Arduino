from flask import Flask, render_template, request
from serial import Serial

serial_com = Serial(port='COM3', baudrate=9600, timeout=3)
app = Flask(__name__)

line = serial_com.readline().decode("utf-8")
print(line)

def ledOn():
    serial_com.write("A".encode())


def ledOff():
    serial_com.write("S".encode())


@app.route("/", methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'on' in request.form.to_dict():
            ledOn()
        if 'off' in request.form.to_dict():
            ledOff()
    return render_template('index.html')


if __name__ == "__main__":
    app.run()
