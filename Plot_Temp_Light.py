# -*- coding: utf-8 -*-
"""
Created on Thu Aug  3 09:40:58 2023

@author: kckus
"""

#Kushum K C and Aalok Sharma Kafle
#Reads data from COM4 and plots the light intensity and temperature from both master and salve.

import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import tkinter as tk

# Create a serial connection
ser = serial.Serial('COM4', 9600)

# Create a new Tkinter window
window = tk.Tk()

# Create a new figure and two subplots, one for each sensor
fig, (ax1, ax2) = plt.subplots(2, 1)

# Create four empty lists to store the data
temp_data_slave = []
light_data_slave = []
temp_data_master = []
light_data_master = []

# Create four lines objects for the plots, with initial data
line1, = ax1.plot([], [], label="Temperature_slave")
line2, = ax2.plot([], [], label="Light intensity_slave")
line3, = ax1.plot([], [], label="Temperature_master", color='orange')
line4, = ax2.plot([], [], label="Light intensity_master", color='orange')

# Set the labels for the axes
ax1.set_ylabel('Temperature (*C)')
ax2.set_ylabel('Light intensity')
ax2.set_xlabel('Time (s)')

# Add legends
ax1.legend(loc="upper left")
ax2.legend(loc="upper left")

# Create a canvas to display the figure in the Tkinter window
canvas = FigureCanvasTkAgg(fig, master=window)
canvas.draw()
canvas.get_tk_widget().pack()

# This function is called periodically from FuncAnimation
def animate(i):

    # Read a line of text from the serial port
    line = ser.readline().decode('utf-8').strip()

    # Split the line of text into four parts at the tab character
    parts = line.split('\t')

    # Extract the numerical part of each string and convert it to a float
    temp_slave = float(parts[0].split(': ')[1].split(' ')[0])
    light_slave = float(parts[1].split(': ')[1])
    temp_master = float(parts[2].split(': ')[1].split(' ')[0])
    light_master = float(parts[3].split(': ')[1])

    # Append the data to the lists
    temp_data_slave.append(temp_slave)
    light_data_slave.append(light_slave)
    temp_data_master.append(temp_master)
    light_data_master.append(light_master)

    # Print the values to the console
    print(f"Temperature_slave: {temp_slave} *C, Light intensity_slave: {light_slave}, Temperature_master: {temp_master} *C, Light intensity_master: {light_master}")

    # Update the lines with the new data
    line1.set_data(range(len(temp_data_slave)), temp_data_slave)
    line2.set_data(range(len(light_data_slave)), light_data_slave)
    line3.set_data(range(len(temp_data_master)), temp_data_master)
    line4.set_data(range(len(light_data_master)), light_data_master)

    # Adjust the axes limits
    ax1.set_xlim(0, max(len(temp_data_slave), len(temp_data_master)))
    ax2.set_xlim(0, max(len(light_data_slave), len(light_data_master)))
    ax1.set_ylim(min(min(temp_data_slave), min(temp_data_master)), max(max(temp_data_slave), max(temp_data_master)))
    ax2.set_ylim(min(min(light_data_slave), min(light_data_master)), max(max(light_data_slave), max(light_data_master)))

    # Redraw the canvas
    canvas.draw()

# Call the animate function every 1000 ms
ani = animation.FuncAnimation(fig, animate, interval=1000)

# Start the Tkinter event loop
tk.mainloop()

# Close the serial connection
ser.close()