<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, DELETE");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

// เชื่อมต่อฐานข้อมูล
$link = mysqli_connect('localhost', 'root', 'fvtg6y7u', 'price01');

// ตั้งค่าการเข้ารหัสเป็น UTF-8
mysqli_set_charset($link, 'utf8');

if (!$link) {
    die(json_encode(["error" => "Connection failed: " . mysqli_connect_error()]));
}

// ตรวจสอบ method
$requestMethod = $_SERVER["REQUEST_METHOD"];

if ($requestMethod == 'GET') {
    if (isset($_GET['row_id']) && !empty($_GET['row_id'])) {
        $id = intval($_GET['row_id']);
        $sql = "SELECT row_id, description, prc01, primary_unit_of_measure, chgdat FROM t2 WHERE row_id = $id";
    } else {
        $sql = "SELECT row_id, description, prc01, primary_unit_of_measure, chgdat FROM t2 ORDER BY chgdat DESC LIMIT 1";
    }

    $result = mysqli_query($link, $sql);

    if (!$result) {
        die(json_encode(["error" => "SQL error: " . mysqli_error($link)]));
    }

    $arr = [];
    while ($row = mysqli_fetch_assoc($result)) {
        $arr[] = $row;
    }

    echo json_encode($arr);
} else {
    echo json_encode(["error" => "Invalid request method"]);
}

// ปิดการเชื่อมต่อฐานข้อมูล
mysqli_close($link);
?>
