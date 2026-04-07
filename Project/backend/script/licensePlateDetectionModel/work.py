from ultralytics import YOLO
from PIL import Image
import easyocr
import cv2
import matplotlib.pyplot as plt
import os
# model = YOLO("C:/Users/Mr.Blue/Desktop\yolov8/licensePlateDetectionModel/model/mark2/weights/best.pt")

# results = model.predict(source='C:/Users/Mr.Blue\Desktop/yolov8/licensePlateDetectionModel/licenplate.jpg', save=True, conf=0.5 , save_crop=True )
imagePath = results[0].save_dir + "\crops\license-plate\licenplate.jpg"
# print(imagePath)

image = Image.open(imagePath)
gray_image = image.convert('L')
# gray_image.save('C:/Users/Mr.Blue/Desktop/yolov8/gray_image.jpg')

reader = easyocr.Reader(['th'])

ocr_results = reader.readtext('C:/Users/Mr.Blue/Desktop/yolov8/gray_image.jpg')

detected_texts = [text for _, text, _ in ocr_results]

data = {
    'id' : detected_texts[0] , 
    'province' : detected_texts[1] ,
    'number' : detected_texts[2]
}

print(data)
