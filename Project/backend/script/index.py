import sys
from ultralytics import YOLO
import os
import cv2
import json
import websocket
from PIL import Image
import easyocr
import matplotlib.pyplot as plt
import torch

import mysql.connector
from datetime import datetime

db = mysql.connector.connect(
    host="localhost",    
    user="root",         
    password="bun0959807082",     
    database="helmetdetectdb"
)

# day = sys.argv[1]
# time = sys.argv[2]




try:
    helmetModel = YOLO("./helmetDetectionModel/model/weights/best.pt")
    # print("Model loaded successfully")
except Exception as e:
    print(f"Error loading model: {e}")
#for test helmet

# results = helmetModel.predict(source='./helmetDetectionModel/unwearing_helmet.jpg')
day = "2025-03-16"
time = "17-46-56test"

# print(day)
#for use
results = helmetModel.predict(source='../uploads/'+day+'/'+time+'/camera_0.jpg')


boxes = results[0].boxes  
names = results[0].names  


detections = []

unwearing_helmet = 0
for i in range(len(boxes.cls)):
    class_id = int(boxes.cls[i])  # ID ของคลาส
    confidence = float(boxes.conf[i])  # แปลง Tensor เป็น float
    detected_class = names[class_id]  # ดึงชื่อคลาสจาก class_id
    if(detected_class == 'Without Helmet'):
        unwearing_helmet += 1

    # detections.append({
    #     "class": detected_class,
    #     "confidence": confidence
    # })

# print(unwearing_helmet)
# json_result = json.dumps({"detections": detections}, indent=4)
# print(json_result)

try:
    licenPlateModel = YOLO("./licensePlateDetectionModel/model/mark2/weights/best.pt")
    # print("Model loaded successfully")
except Exception as e:
    print(f"Error loading model: {e}")


#for test license plate
# results = licenPlateModel.predict(source='./licensePlateDetectionModel/licenplate.jpg', save=True , save_crop=True )

#for use
licenPlateResult = licenPlateModel.predict(source='../uploads/'+day+'/'+time+'/camera_1.jpg', save=True , save_crop=True )
# print(results[0].save_dir) 
imagePath = results[0].save_dir +"\crops\license-plate\camera_1.jpg"


image = Image.open(imagePath)
gray_image = image.convert('L')
gray_image.save("./licensePlateDetectionModel/temp_gray.jpg")

reader = easyocr.Reader(['th'] , gpu=True)

ocr_results = reader.readtext('./licensePlateDetectionModel/temp_gray.jpg')

detected_texts = [text for _, text, _ in ocr_results]

# plateLicenNumber = {
#     'id' : detected_texts[0] , 
#     'province' : detected_texts[1] ,
#     'number' : detected_texts[2]
# }

# print(plateLicenNumber)





cursor = db.cursor()

licenplate = detected_texts[0]+","+detected_texts[1]+","+detected_texts[2]

helmetDetect = 1
if(unwearing_helmet > 0):
    helmetDetect = 0

datetime1 = datetime.now()
file = '/uploads/'+day+'/'+time

# print("datetime: ")
# print( datetime1)
# print("helmetDetect: ")
# print(helmetDetect)
# print("licenplate: ")
# print(licenplate)
# print("file: ")
# print(file)

sql = "INSERT INTO detection_log (helmetDetect, licenplate, file , detect_at) VALUES (%s, %s, %s , %s)"
val = (helmetDetect,licenplate, file , datetime1)
cursor.execute(sql, val)

db.commit()
cursor.close()
db.close()

