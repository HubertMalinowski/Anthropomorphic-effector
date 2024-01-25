import cv2
import numpy as np
import paho.mqtt.client as mqtt
from cvzone.HandTrackingModule import HandDetector

# Konfiguracja połączenia MQTT
broker = "192.168.1.128"  # Wprowadź adres brokera MQTT
port = 1883  # Port brokera MQTT
topic = "Array_of_fingers"  # Wprowadź nazwę tematu, na którym będą publikowane dane

# Konfiguracja detektora dłoni
detector = HandDetector(detectionCon=0.8, maxHands=2)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Połączono z brokerem MQTT")
    else:
        print("Błąd połączenia z brokerem MQTT")

def on_publish(client, userdata, mid):
    print("Dane zostały opublikowane na temacie MQTT")

client = mqtt.Client()
client.on_connect = on_connect
client.on_publish = on_publish
client.connect(broker, port)

cap = cv2.VideoCapture(0)  # Otwórz strumień wideo z kamery

while True:
    success, img = cap.read()  # Odczytaj obraz z kamery

    # Znajdź dłonie na obrazie
    hands, img = detector.findHands(img)

    if hands:
        hand = hands[0]  # Wybierz pierwszą znalezioną dłoń

        # Sprawdź, jakie palce są uniesione
        fingers = detector.fingersUp(hand)

        # Przekształć tablicę palców na int
        fingers_int = 100000
        if fingers[0] == 1:
            fingers_int = fingers_int + 1
        if fingers[1] == 1:
            fingers_int = fingers_int + 10
        if fingers[2] == 1:
            fingers_int = fingers_int + 100
        if fingers[3] == 1:
            fingers_int = fingers_int + 1000
        if fingers[4] == 1:
            fingers_int = fingers_int + 10000
            
        # Wyślij palce przekształcone na int jako wiadomość MQTT
        message = np.array(fingers).tostring()
        print(fingers_int)
        client.publish(topic, payload=fingers_int)

    cv2.imshow("Image", img)  # Wyświetl obraz

    if cv2.waitKey(1) == ord('q'):  # Zakończ program po naciśnięciu klawisza 'q'
        break

cap.release()  # Zwolnij strumień wideo
cv2.destroyAllWindows()

