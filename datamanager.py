"""
A python handeler for thresholding data from a VL53L1X sensor
Yes I know its horific code and I'm not sorry.
"""
import serial
import numpy
import csv

MAX_SIZE = 10
CSV_FILE_NAME = "data.csv"


def new_data_into_list(last_data):
    """Add new data to the a given list from the serial port"""
    new_data = False

    while not new_data:
        data = serial_port.readline()[:4]
        try:
            data = int(data)
            last_data.append(data)
            new_data = True
        except ValueError:
            print(f'Could not convert {data} to type int trying again')

    return data


if __name__ == "__main__":
    serial_port = serial.Serial('COM6', 9600)
    print(f"created serial object {serial_port}")

    last_data = []

    for i in range(MAX_SIZE):
        new_data_into_list(last_data)

    while True:
        data_trusted = True
        data = new_data_into_list(last_data)
        last_data.pop(0)  # Remove the last value from the list

        # Decide if it is valid data
        polyfit = numpy.polyfit(range(len(last_data)), last_data, 1)
        cololation = numpy.corrcoef(last_data, range(len(last_data)))
        sd = numpy.std(last_data)

        """
        Don't trust the data if we are out of range of the sensor.
        If the data is spread out then it is either noise or that we are moving
        If we are moving back or forth then the distance is corolated against
        time and so if we have a corolation of more than 0.75 then we trust the
        sensor.
        """
        if data > 3000 or ((sd > 200) and (abs(cololation[0][1]) <= 0.75)):
            data_trusted = False

        if data_trusted:
            print(f"polyfit {polyfit[0]:.3f} corolation: {cololation[0][1]:.3f} sd: {sd:.3f} data: {data}")

            with open(CSV_FILE_NAME, mode='a') as data_file:
                data_file = csv.writer(data_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                data_file.writerow([polyfit[0], cololation[0][1], sd, data])
        else:
            print('MISSED DATA')

