<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, DELETE");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

// ตั้งค่าการเชื่อมต่อ MySQL
$servername = "localhost";
$username = "root";
$password = "fvtg6y7u";
$dbname = "price01";

// สร้างการเชื่อมต่อ
$conn = new mysqli($servername, $username, $password, $dbname);

// ตรวจสอบการเชื่อมต่อ
if ($conn->connect_error) {
    die(json_encode(array("error" => "Connection failed: " . $conn->connect_error)));
}

// ตั้งค่าการเข้ารหัสเป็น UTF-8
$conn->set_charset("utf8");

// ฟังก์ชันกรองเฉพาะตัวอักษรภาษาไทยและตัวเลข
function extractThaiAndNumbers($input) {
    $thaiChars = "กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรฤลฦวศษสหฬอฮฯะัาำิีึืุูเแโใไๅๆ็่้๊๋์";
    $thaiStart = -1;
    for ($i = 0; $i < mb_strlen($input); ++$i) {
        if (mb_strpos($thaiChars, mb_substr($input, $i, 1)) !== false) {
            $thaiStart = $i;
            break;
        }
    }
    if ($thaiStart != -1) {
        return mb_substr($input, $thaiStart);
    }
    return $input;
}

// ตรวจสอบ method
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $input = json_decode(file_get_contents('php://input'), true);
    if (isset($input['product_id'])) {
        $productId = intval($input['product_id']);
        
        // คิวรีดึงข้อมูลสินค้าตาม id
        $sql = "SELECT row_id, description, prc01, primary_unit_of_measure, chgdat, stkcod FROM t2 WHERE row_id = $productId";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            // กรองเฉพาะตัวอักษรภาษาไทยและตัวเลขใน description
            $description_filtered = extractThaiAndNumbers($row["description"]);
            $data = array(
                "row_id" => $row["row_id"],
                "description" => $description_filtered,
                "prc01" => (float) $row["prc01"], // แปลงเป็น float
                "primary_unit_of_measure" => $row["primary_unit_of_measure"],
                "chgdat" => $row["chgdat"],
                "stkcod" => $row["stkcod"]
            );
        } else {
            $data = array("error" => "No data found");
        }

        // ปิดการเชื่อมต่อ
        $conn->close();

        // ส่งข้อมูลไปยัง ESP32
        echo json_encode($data, JSON_UNESCAPED_UNICODE); // เพิ่ม JSON_UNESCAPED_UNICODE เพื่อให้แสดงภาษาไทยได้
    } else {
        echo json_encode(array("error" => "Invalid request"));
    }
} else {
    echo json_encode(array("error" => "Invalid request"));
}
?>
