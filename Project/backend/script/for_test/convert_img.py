import os
from PIL import Image

# กำหนดโฟลเดอร์ที่มีไฟล์ .jfif
input_folder = "./helmet"  # <-- เปลี่ยน path นี้ให้ตรงกับโฟลเดอร์ของคุณ
output_folder = os.path.join(input_folder, "converted_jpg")

# สร้างโฟลเดอร์ output หากยังไม่มี
os.makedirs(output_folder, exist_ok=True)

# วนลูปแปลงไฟล์ .jfif ทุกไฟล์ในโฟลเดอร์
for filename in os.listdir(input_folder):
    if filename.lower().endswith(".jfif"):
        input_path = os.path.join(input_folder, filename)
        output_filename = os.path.splitext(filename)[0] + ".jpg"
        output_path = os.path.join(output_folder, output_filename)
        
        try:
            with Image.open(input_path) as img:
                rgb_img = img.convert("RGB")
                rgb_img.save(output_path, "JPEG")
                print(f"แปลงแล้ว: {filename} → {output_filename}")
        except Exception as e:
            print(f"❌ แปลงไม่สำเร็จ: {filename} ({e})")

print("เสร็จสิ้นการแปลงไฟล์ทั้งหมด ✅")