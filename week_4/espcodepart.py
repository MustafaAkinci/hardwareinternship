import machine
import time
import ujson
from umqtt.simple import MQTTClient
# Seri bağlantıyı yapılandırın (örneğin, UART1)
uart = machine.UART(1, baudrate=9600, tx=33, rx=32)  # TX ve RX pinleri ESP32'nin kullandığı pinlere göre ayarlayın
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
    mqtt_broker = "91.121.93.94"  # MQTT broker (sunucu) IP adresi
    mqtt_topic = "esp32_data"  # MQTT konusu
    mqtt_client = "esp32_client"  # MQTT istemci adı
    # MQTT istemcisini oluşturun ve bağlanın
    client = MQTTClient(mqtt_client, mqtt_broker)
    client.connect()
    while True:
        # Arduino'dan gelen verileri okuyun
        data = uart.read()
        if data:
            # Potansiyometre açı değerini MQTT konusuna yayınlayın
            client.publish(mqtt_topic, data)
        time.sleep(1)  # Verileri belirli bir sıklıkta okumak için uygun bir bekleme süresi ayarlayın
    # Bağlantıyı kapatın
    client.disconnect()

