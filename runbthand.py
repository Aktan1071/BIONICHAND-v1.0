# Aşağıda Kütüphanelerin Tanımlamaları yapılmıştır. HandTrackingModule el algılama için açık koynak yayından alınmıştır.
import bluetooth
import time as tm
import sys
import keyboard
from HandTrackingModule import *
import cv2

# Gönderilen char değerleri updatehistory ile filitrelenmiş ve aynı değerin arka arkaya iletilmesini engellemiştir.
# Filitre Kodu aşağıda if satırında verilmiştir (176. satır).
updatehistory = None

print("----- Bionic Hand v1.0 -----")
time.sleep(1)

# Görüntünün alınabilmesi için webcam seçilmiştir.
# Detector üzerine El algılama fonksiyonu yazılmıştır.

#################################################
cap = cv2.VideoCapture(0)
detector = handDetector(maxHands=1, detectionCon=0.7)
#################################################
time.sleep(1)

# Blyetooth modülü ile bağlantıya geçebilmek için cihaz taraması gerçekleştirilmiştir.

"""
nearby_devices = bluetooth.discover_devices(lookup_names=True)
print("Found {} devices.".format(len(nearby_devices)))

for addr, name in nearby_devices:
    print("  {} - {}".format(addr, name))"""

# Bluetooth Cihazı belirlendikten sonra btadrr üzerine cihaz kimliği girilir.
# 1 Portu üzerinden Connecting işlemi gerçekleştirilir.

btaddr = "98:D3:31:F9:88:85"
port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((btaddr, port))
print("Bluetooth Has Connected...")
time.sleep(1)
print("Camera Has Connected...")
time.sleep(1)
print("Bionic Hand Has Connected...")
print("\nPress ESC To Exit")
#################################################
while True:
# Bluetooth bağlantısı hatasız tamamlandıktan sonra Görüntü işleme başlatılır ve döngü içinde kameradaki resim verileri anlık olarak çekilir.
    #################################################
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    #################################################
# fingerdata fonksiyonu ile eldeki 32 farklı parmak kombinasyonları bir karakter değişkenine atanır.

    def fingerdata():
        if lmList:
            # Parmakların açıklığı fingersUp üerinden fingers listine aktarılır ve if else ile açıklık durumu kontrol edilir.
            fingers = detector.fingersUp()
            while True:
                # C5_0 #
                # Ek. C5-0 kombinasyon işleminin elemanlarını ifade etmektedir.

                if fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 0:
                    return "0"

                # C5_1-C5_4 #

                elif fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 0:
                    return "q"

                elif fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 0:
                    return "w"

                elif fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 0:
                    return "6"

                elif fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 0:
                    return "r"

                elif fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 1:
                    return "t"
                #############
                elif fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 1:
                    return "y"

                elif fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 1:
                    return "u"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 1:
                    return "i"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 1:
                    return "o"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 0:
                    return "p"

                # C5_2-C5_3 #

                if fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 0:
                    return "a"

                if fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 0:
                    return "s"

                if fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 0:
                    return "d"

                if fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 1:
                    return "f"

                if fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 1:
                    return "g"

                if fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 0:
                    return "h"

                if fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 0:
                    return "j"

                if fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 0:
                    return "k"

                if fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 1:
                    return "l"

                if fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 1:
                    return "z"

                #############

                elif fingers[0] == 0 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 1:
                    return "x"

                elif fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 1:
                    return "c"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 0 and fingers[4] == 1:
                    return "v"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 0:
                    return "b"

                elif fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 0:
                    return "n"

                elif fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 1:
                    return "m"

                elif fingers[0] == 0 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 1:
                    return "2"

                elif fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 0 and fingers[4] == 1:
                    return "3"

                elif fingers[0] == 1 and fingers[1] == 0 and fingers[2] == 1 and fingers[3] == 1 and fingers[4] == 0:
                    return "4"

                elif fingers[0] == 1 and fingers[1] == 1 and fingers[2] == 0 and fingers[3] == 1 and fingers[4] == 0:
                    return "5"

                # C5_5 # #11111

                else:
                    return "1"

# Kameradan çekilen veri ekrana yazdırılır.
#################################################
    cv2.imshow("Image", img)
    cv2.waitKey(1)

# Bluetooth üzerinden cihaza karakter değeri iletilir.
#################################################
    if str(fingerdata()) != str(updatehistory):
        updatehistory = fingerdata()
        sock.send(str(fingerdata()))
        print("Data: " + str(fingerdata()))
        # Aşağıdaki satır if içine eklenilerek son parmak kombinasyonu hatırlama fonksiyonu deaktif edilebilir.
        # and str(fingerdata()) != str(None)
    #################################################

# Eğer Klavyeden ESC tuşuna basılırsa program sonlandırılır.
    elif keyboard.is_pressed('Esc'):
        sock.close()
        print("GoodBye...")
        tm.sleep(1)
        sys.exit()
