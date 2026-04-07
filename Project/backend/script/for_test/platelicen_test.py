from ultralytics import YOLO
from PIL import Image
import easyocr
import os

# โหลดโมเดล YOLO
try:
    licenPlateModel = YOLO("../licensePlateDetectionModel/model/mark2/weights/best.pt")
    print("✅ Model loaded successfully")
except Exception as e:
    print(f"❌ Error loading model: {e}")
    exit()

# โฟลเดอร์ภาพ
input_folder = "./plate_licen"  # แก้ตามชื่อโฟลเดอร์ของคุณ
output_folder = "./cropped_plates"
os.makedirs(output_folder, exist_ok=True)

# วนลูปภาพในโฟลเดอร์
for filename in os.listdir(input_folder):
    if filename.lower().endswith(('.jpg', '.jpeg', '.png')):
        image_path = os.path.join(input_folder, filename)
        print(f"🔍 Predicting: {filename}")
        
        # ใช้ YOLO พยากรณ์
        results = licenPlateModel.predict(image_path, conf=0.25)

        # เปิดภาพด้วย PIL
        img = Image.open(image_path)

        for i, result in enumerate(results):
            boxes = result.boxes

            if boxes is None or len(boxes) == 0:
                print(f"❗ ไม่พบป้ายทะเบียนใน {filename}")
                continue

            for j, box in enumerate(boxes):
                # ตำแหน่งกรอบ
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                cropped = img.crop((x1, y1, x2, y2))

                # บันทึกภาพที่ crop แล้ว
                cropped_filename = f"{os.path.splitext(filename)[0]}_plate_{j+1}.jpg"
                cropped_path = os.path.join(output_folder, cropped_filename)
                cropped.save(cropped_path)
                print(f"✅ ครอปแล้ว: {cropped_filename}")


input_folder = "./cropped_plates"
reader = easyocr.Reader(['th', 'en'])  # รองรับป้ายทะเบียนไทยและอังกฤษ

for filename in os.listdir(input_folder):
    if filename.lower().endswith(('.jpg', '.jpeg', '.png')):
        image_path = os.path.join(input_folder, filename)
        print(f"🔍 อ่านป้ายทะเบียนจาก: {filename}")

        try:
            # เปิดภาพและแปลงเป็น grayscale
            image = Image.open(image_path).convert("L")

            # บันทึกภาพ grayscale ชั่วคราว (ไม่เซฟจริง) โดยแปลงเป็น numpy array
            import numpy as np
            gray_image_np = np.array(image)

            # อ่านข้อความจากภาพสีเทา
            results = reader.readtext(gray_image_np)

            if results:
                print("📝 ข้อความที่พบ:")
                for (bbox, text, confidence) in results:
                    print(f"  ▶ '{text}' (ความมั่นใจ: {confidence:.2f})")
            else:
                print("❌ ไม่พบข้อความในภาพนี้")

        except Exception as e:
            print(f"⚠️ เกิดข้อผิดพลาดในการอ่านภาพ {filename}: {e}")

print("✅ เสร็จสิ้นการอ่านป้ายทะเบียนทุกไฟล์")
