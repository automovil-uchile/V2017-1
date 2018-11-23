# Electromobility

## EL5004 - Taller de Diseño 2018 - Beauchef Proyecta

The following repository holds the documentation of the work done for the course EL5004. The scope of the work is to develop an electric car from the perspective of power electronics, control, communications and hardware.

## How to use this repository?

If all you want is to access the code to make your own electric car control system, please look at the /code folder. Inside it there are the necessary files to make all happen. Follow the instructions in the next url https://www.arduino.cc/en/Guide/Libraries to install correctly the library. The program is mainly written in C++, so you must be in some level familiar with it to modify the codes. The code was tested under the Arduino UNO and DUE boards, but is highly recommended to use the last one, because of the number of I/O connections required. There is a Python early version of the control systems with some kind of signal visualization, developed for the platform Raspberry Pi.

Our first work started at Spring 2017. It was almost bibliography review and design of the main electrical systems. There are auxiliary programs inside folders /spi, /sensor_direccion and /scripts_sensor_dir_simulado. The first one is an adaptation of SPI communication protocol for the board UNO, where it acts as Master and the sensors hardware as Slaves. Folder /sensor_direccion has the code to read the yaw angle sensor and the last folder is a simulation of the output from the yaw sensor to test how the machine reads the information.

Any questions through GitHub only. 
