import os
import easyocr
from PIL import Image

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
