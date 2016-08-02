# mbed-os-example-client-withTempHum

This is a simple example of mbed client with Grove Temperature&Humidity Sensor working for temperature&humidity detection in real time with mbed OS. You may need to take a look at [mbed-client-quickstart](https://github.com/ARMmbed/mbed-client-quickstart) first to finish the device registration.

The application:

* Registers with mbed Device Connector.
* Gives mbed Device Connector access to its resources (read and write).
* Records the number of clicks on the device’s button and temperature&humidity detected by the sensor and sends them to mbed Device Connector.

## Application resources

 three [resources](https://docs.mbed.com/docs/mbed-device-connector-web-interfaces/en/latest/#the-mbed-device-connector-data-model) are included:

* `Button (3200/0/5501)`.  Number of presses of SW2 (GET).
* `Temperature(3300/0/5700)`. The current temperature value, updated every two seconds.
* `Humidity(3300/0/5701)`. The current humidity value, updated every two seconds.

## Required hardware

* An [FRDM-K64F](http://developer.mbed.org/platforms/frdm-k64f/) board with [Grove temperature&humidity sensor](https://developer.mbed.org/components/Grove-TempHumi-Sensor/).
* An Ethernet connection to the internet.
* An Ethernet cable.
* A micro-USB cable.

## Required software

* An [ARM mbed account](https://developer.mbed.org/account/login/?next=/).
* [mbed-cli]( https://github.com/ARMmbed/mbed-cli) - to build the example programs. To learn how to build mbed OS applications with mbed-cli, see [the user guide]( https://github.com/ARMmbed/mbed-cli/blob/master/README.md).
* A [serial port monitor](https://developer.mbed.org/handbook/SerialPC#host-interface-and-terminal-applications).

## Build the program
To build the example application:
1.	Clone [this]( https://github.com/MaggieMei/mbed-os-example-client-withTempHum) repository: `git clone https://github.com/MaggieMei/mbed-os-example-client-withTempHum`
2.	Change to the project directory and deploy the mbed program with `mbed deploy`
3.	Update mbed-os sources using the `mbed update` command.
4.	Import DHT22 lib which is used for temperature & humidity sample: `mbed add https://developer.mbed.org/users/Julepalme/code/DHT22/`
5.	Go to [mbed Device Connector]( https://connector.mbed.com/) and log in with your mbed account. Then go to My Devices > Security credentials and click the `Get my device security credentials` button to get new credentials for your device. Replace the contents in security.h of this project's directory with content copied above.
6.	Build the application by selecting the hardware board and build the toolchain using the command `mbed compile -m K64F -t GCC_ARM -c -j0`. mbed-cli builds a binary file under the project’s `.build` directory.
7.	Plug the Ethernet cable into the board if you are using Ethernet mode.
8.	Drag the binary .build/K64F/GCC_ARM/mbed-os-example-client-withTempHum.bin to the board to flash the application.
9.	The board is automatically programmed with the new binary. A flashing LED on it indicates that it is still working. When the LED stops blinking, the board is ready to work.
10.	Press the RESET button on the board to run the program.

## Monitoring the application

The application prints debug messages over the serial port, so you can monitor its activity with a serial port monitor. The application uses baud rate 115200.

**Note:** Instructions to set this up are located [here](https://developer.mbed.org/handbook/SerialPC#host-interface-and-terminal-applications).

After the bin file downloaded and your board reset, you should see the messages as below:

```
Starting mbed Client example...
Using Ethernet

Connected to Network successfully
IP address 10.164.2.82

SOCKET_MODE : UDP
Connecting to coap://api.connector.mbed.com:5684
Registered object successfully!
```

**Note:** Device name is the endpoint name you will need later on [Testing the application](https://github.com/MaggieMei/mbed-client-withTempHum#testing-the-application) chapter.

After you click the `SW2` button on your board you should see messages about the value changes:

```
handle_button_click, new value of counter is 1
```

Every two seconds updated values of temperature and humidity should be displayed on the Terminal.

```
the current temperature is: 27.30, the current humidity is: 77.50
```

## Testing the application

1. After device registration finished, go to [My devices > Connected devices](https://connector.mbed.com/#endpoints). Your device should be listed here.
2. Press the `SW2` button on the device a number of times (make a note of how many times you did that).
3. Go to [Device Connector > API Console](https://connector.mbed.com/#console).
4. Enter `https://api.connector.mbed.com/endpoints/DEVICE_NAME/3200/0/5501` in the URI field and click **TEST API**. Replace `DEVICE_NAME` with your actual endpoint name. The device name can be found in the `source/security.h` file, see variable `MBED_ENDPOINT_NAME` or it can be found from the traces [Monitoring the application](https://github.com/ARMmbed/mbed-client-quickstart#monitoring-the-application).
5. The number of times you pressed `SW2` is shown.
6. Enter `https://api.connector.mbed.com/endpoints/DEVICE_NAME/3300/0/5700` in the URI field and click **TEST API**.
7. The value of current temperature will be shown.
8. Enter `https://api.connector.mbed.com/endpoints/DEVICE_NAME/3300/0/5701` in the URI field and click **TEST API**.
9. The value of current humidity will be shown.
10. Press the `SW3` button to unregister from mbed Device Connector. You should see `Unregistered Object Successfully` printed to the serial port and LED starts blinking. This will also stop your application. Press the `RESET` button to run the program again.

**NOTE:** If you get an error, for example `Server Response: 410 (Gone)`, clear your browser's cache, log out, and log back in. 
**NOTE:** Only GET methods can be executed through [Device Connector > API Console](https://connector.mbed.com/#console). For the other methods check the [mbed Device Connector Quick Start](https://github.com/ARMmbed/mbed-connector-api-node-quickstart).
