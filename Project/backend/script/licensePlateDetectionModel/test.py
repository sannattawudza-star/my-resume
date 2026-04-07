from ultralytics import YOLO

model = YOLO("C:/Users/Mr.Blue/Desktop/yolov8/licensePlateDetectionModel/model/mark2/weights/best.pt")

results = model.predict(source='C:/Users/Mr.Blue/Desktop/yolov8/licensePlateDetectionModel/test' , save=True, conf=0.5)


for result in results:
    print(result)