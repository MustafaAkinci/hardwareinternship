import machine
import time
import ujson
from umqtt.simple import MQTTClient
# Configure the serial connection (for example, UART1)
uart = machine.UART(1, baudrate=9600, tx=33, rx=32)  # Set TX and RX pins according to the pins used by ESP32
def connect_wifi():
    import network
    ssid = "Akıncı"
    password = "123456asdf"
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("Establishing WiFi connection...")
        wlan.connect(ssid, password)
        if wlan.isconnected():
            pass
    print("WiFi connection established successfully")
    print(wlan.ifconfig())
def start():
    mqtt_broker = "91.121.93.94" # MQTT broker (server) IP address
    mqtt_topic = "esp32_data"  # MQTT topic
    mqtt_client = "esp32_client"  # MQTT client name
   # Create MQTT client and connect
    client = MQTTClient(mqtt_client, mqtt_broker)
    client.connect()
    while True:
        # Read data from Arduino
        data = uart.read()
        if data:
            # Publish potentiometer angle value to MQTT topic
            client.publish(mqtt_topic, data)
        time.sleep(1) # Set a suitable waiting time to read data at a certain frequency
    # Close the connection
    client.disconnect()

