/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "minar/minar.h"
#include "security.h"
#include "simpleclient.h"
#include "lwipv4_init.h"
#include "DHT22.h"
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

using namespace mbed::util;

Serial &output = get_stdio_serial();

EthernetInterface eth;
Ticker flipper;
Ticker flipper_temp;
Ticker flipper_hum;
DHT22 dht22(D4);

// These are example resource values for the Device Object
struct MbedClientDevice device = {
    "Manufacturer_String",      // Manufacturer
    "Type_String",              // Type
    "ModelNumber_String",       // ModelNumber
    "SerialNumber_String"       // SerialNumber
};

// Instantiate the class which implements LWM2M Client API (from simpleclient.h)
MbedClient mbed_client(device);

// Set up Hardware interrupt button.
InterruptIn obs_button(SW2);
InterruptIn unreg_button(SW3);

// LED Output
DigitalOut led2(LED2);
DigitalOut led3(LED3);

/*
 * The button contains one property (click count).
 * When `handle_button_click` is executed, the counter updates.
 */
class ButtonResource {
public:
    ButtonResource() {
        // create ObjectID with metadata tag of '3200', which is 'digital input'
        btn_object = M2MInterfaceFactory::create_object("3200");
        M2MObjectInstance* btn_inst = btn_object->create_object_instance();
        // create resource with ID '5501', which is digital input counter
        M2MResource* btn_res = btn_inst->create_dynamic_resource("5501", "Button",
            M2MResourceInstance::INTEGER, true /* observable */);
        // we can read this value
        btn_res->set_operation(M2MBase::GET_ALLOWED);
        // set initial value (all values in mbed Client are buffers)
        // to be able to read this data easily in the Connector console, we'll use a string
        btn_res->set_value((uint8_t*)"0", 1);
    }

    M2MObject* get_object() {
        return btn_object;
    }

    /*
     * When you press the button, we read the current value of the click counter
     * from mbed Device Connector, then up the value with one.
     */
    void handle_button_click() {
        M2MObjectInstance* inst = btn_object->object_instance();
        M2MResource* res = inst->resource("5501");

        // up counter
        counter++;

        printf("handle_button_click, new value of counter is %d\r\n", counter);

        // serialize the value of counter as a string, and tell connector
        stringstream ss;
        ss << counter;
        std::string stringified = ss.str();
        res->set_value((uint8_t*)stringified.c_str(), stringified.length());
    }

private:
    M2MObject* btn_object;
    uint16_t counter = 0;
};

/* 
 * Warning function when the temparature gets higher than 32 degrees
 * LED2 will keep blinky
 */
void flip1() {
    led2 = !led2;
}

/* 
 * Warning function when the humidity gets higher than 120%rh
 * LED3 will keep blinky
 */
void flip2() {
    led3 = !led3;
}

/*
 * The Temp&Hum sensor contains two property(temparature & humidity)
 * When "handle_temphum" is executed, the new temparature and humidity will be obtained from the sensor.
 */
class TempHumResource {
public:
    TempHumResource() {
        // create ObjectID with metadata tag of '3300', which is 'digital input'
        temphum_object = M2MInterfaceFactory::create_object("3300");
        M2MObjectInstance* temphum_inst = temphum_object->create_object_instance();
		
        // create resource with ID '5700', which is the current temperature value
        M2MResource* temp = temphum_inst->create_dynamic_resource("5700", "Current Temperature",
            M2MResourceInstance::FLOAT, true /* observable */);
        // we can read & write this value
        temp->set_operation(M2MBase::GET_PUT_POST_ALLOWED);
        // set initial value (all values in mbed Client are buffers)
        // to be able to read this data easily in the Connector console, we'll use a string
        temp->set_value((uint8_t*)"25", 2);
        
        // create resource with ID '5701', which is the current humdity value
        M2MResource* hum = temphum_inst->create_dynamic_resource("5701", "Current Humdity",
            M2MResourceInstance::FLOAT, true /* observable */);
        // we can read & write this value
        hum->set_operation(M2MBase::GET_PUT_POST_ALLOWED);
        // set initial value (all values in mbed Client are buffers)
        // to be able to read this data easily in the Connector console, we'll use a string
        hum->set_value((uint8_t*)"70", 2);
    }

    M2MObject* get_object() {
        return temphum_object;
    }
	
    /*
     * The function handle_temphum will be executed every two seconds
     * to get the new value of temperature and humidity
     * and then up the value with the new one.
     */
    void handle_temphum() {
        M2MObjectInstance* inst = temphum_object->object_instance();
        M2MResource* temp = inst->resource("5700");
        M2MResource* hum = inst->resource("5701");
        float temp_value = 0.00, hum_value = 0.00; // used to store the new values
        int error = 0;
		
	error = dht22.sample();
        // read successfully
        if (1 == error) {
            // Get the temparature & humidity value from the sensor
            temp_value = dht22.getTemperature()/10.0f;
            hum_value = dht22.getHumidity()/10.0f;
            printf("the current temperature is: %2.2f, the current humidity is: %2.2f  \r\n", temp_value, hum_value);
            
            // Send out the warnings when temp&hum get too high
            if (temp_value > 32)
                flipper_temp.attach(&flip1, 2.0);
            if (hum_value > 120)
                flipper_hum.attach(&flip2, 2.0);
            
        } else {  // read unsuccessfully
            printf("Error: %d\n", error);
        }
        
        // update the values in the temp&hum resource
        stringstream ss_temp, ss_hum;
        ss_temp << temp_value;
        std::string stringified_temp = ss_temp.str();
        temp->set_value((uint8_t*)stringified_temp.c_str(), stringified_temp.length());
        ss_hum << hum_value;
        std::string stringified_hum = ss_hum.str();
        hum->set_value((uint8_t*)stringified_hum.c_str(), stringified_hum.length());
    }

private:
    M2MObject* temphum_object;
};

void app_start(int /*argc*/, char* /*argv*/[]) {

    //Sets the console baud-rate
    output.baud(115200);
    output.printf("In app_start()\r\n");

    // This sets up the network interface configuration which will be used
    // by LWM2M Client API to communicate with mbed Device server.
    eth.init();     //Use DHCP
    if (eth.connect() != 0) {
        output.printf("Failed to form a connection!\r\n");
    }
    if (lwipv4_socket_init() != 0) {
        output.printf("Error on lwipv4_socket_init!\r\n");
    }
    output.printf("IP address %s\r\n", eth.getIPAddress());
    output.printf("Device name %s\r\n", MBED_ENDPOINT_NAME);

    // we create our button temp&hum resources
    auto button_resource = new ButtonResource();
    auto temphum_resource = new TempHumResource();
    led2 = led3 = 1; // turn off the leds

    // Unregister button (SW3) press will unregister endpoint from connector.mbed.com
    unreg_button.fall(&mbed_client, &MbedClient::test_unregister);

    // Observation Button (SW2) press will send update of endpoint resource values to connector
    obs_button.fall(button_resource, &ButtonResource::handle_button_click);
    
    // update the temp&hum every two seconds
    flipper.attach(temphum_resource, &TempHumResource::handle_temphum, 2.0);
	
    // Create endpoint interface to manage register and unregister
    mbed_client.create_interface();

    // Create Objects of varying types, see simpleclient.h for more details on implementation.
    M2MSecurity* register_object = mbed_client.create_register_object(); // server object specifying connector info
    M2MDevice*   device_object   = mbed_client.create_device_object();   // device resources object

    // Create list of Objects to register
    M2MObjectList object_list;

    // Add objects to list
    object_list.push_back(device_object);
    object_list.push_back(button_resource->get_object());
    object_list.push_back(temphum_resource->get_object());

    // Set endpoint registration object
    mbed_client.set_register_object(register_object);

    // Issue register command.
    FunctionPointer2<void, M2MSecurity*, M2MObjectList> fp(&mbed_client, &MbedClient::test_register);
    minar::Scheduler::postCallback(fp.bind(register_object,object_list));
    minar::Scheduler::postCallback(&mbed_client,&MbedClient::test_update_register).period(minar::milliseconds(25000));
}
