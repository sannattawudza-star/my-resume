
from ultralytics import YOLO
import os





import matplotlib.pyplot as plt



try:
    helmetModel = YOLO("../helmetDetectionModel/model/weights/best.pt")
    # print("Model loaded successfully")
except Exception as e:
    print(f"Error loading model: {e}")


input_folder = "./helmet"

for filename in os.listdir(input_folder):
    if filename.lower().endswith(('.jpg', '.jpeg', '.png')):
        image_path = os.path.join(input_folder, filename)
        print(f"🔍 Predicting: {filename}")
        
        try:
            # ทำการ predict
            results = helmetModel.predict(image_path, save=True)


        except Exception as e:
            print(f"❌ Predict failed: {filename} ({e})")

print("✅ เสร็จสิ้นการพยากรณ์ทุกไฟล์")



