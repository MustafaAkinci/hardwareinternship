import machine
import time
from umqtt.simple import MQTTClient

uart = machine.UART(1, baudrate=9600, tx=33, rx=32)

def connect_wifi():
    import network
    
    ssid = "Galaxy M31F7F8"
    password = "123456asdf"
    
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    
    if not wlan.isconnected():
        print("Establishing WiFi connection...")
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print("WiFi connection established successfully")
    print(wlan.ifconfig())

def publish_data(data = uart.read()):
    mqtt_server = "95.183.155.169"  
    mqtt_topic = "esp32_data" 
    mqtt_client = "esp32_client"  
    
    client = MQTTClient(mqtt_client, mqtt_server)
    client.connect()
    
    print("Sending data to MQTT server: ", data)
    client.publish(mqtt_topic, data)
    
    client.disconnect()

def main():
    connect_wifi()
    while True:
        data = uart.read()
        if data:
            decoded_data = data.decode("utf-8")
            print("Arduino data received: ", decoded_data)
            publish_data(decoded_data)
        
        time.sleep(1) 

if __name__ == "__main__":
    main()

