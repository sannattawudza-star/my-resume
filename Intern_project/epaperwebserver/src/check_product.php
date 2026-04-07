<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

$servername = "localhost";
$username = "root"; // แก้ให้ตรงกับ MySQL ของคุณ
$password = "fvtg6y7u"; // แก้ให้ตรงกับ MySQL ของคุณ
$dbname = "price01";

// เชื่อมต่อฐานข้อมูล
$link = new mysqli($servername, $username, $password, $dbname);
if ($link->connect_error) {
    die(json_encode(["error" => "Connection failed: " . $link->connect_error]));
}

// ตั้งค่าการเข้ารหัสเป็น UTF-8
$link->set_charset("utf8");

$product_id = isset($_GET['product_id']) ? $link->real_escape_string($_GET['product_id']) : '';

$sql = "SELECT description, prc01, chgdat FROM t2 WHERE stkcod = '$product_id'";
$result = $link->query($sql);

if ($result && $result->num_rows > 0) {
    $product = $result->fetch_assoc();
    echo json_encode(["exists" => true, "product" => $product]);
} else {
    echo json_encode(["exists" => false]);
}

$link->close();
?>
