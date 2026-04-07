<?php
require 'vendor/autoload.php';

use Picqer\Barcode\BarcodeGeneratorHTML;

header("Access-Control-Allow-Origin: *");
header("Content-Type: text/html; charset=UTF-8");
header("Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, DELETE");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

error_reporting(E_ALL);
ini_set('display_errors', 1);

$servername = "localhost";
$username = "root"; // แก้ให้ตรงกับ MySQL ของคุณ
$password = "fvtg6y7u"; // แก้ให้ตรงกับ MySQL ของคุณ
$dbname = "price01";

// เชื่อมต่อฐานข้อมูล
$link = new mysqli($servername, $username, $password, $dbname);
if ($link->connect_error) {
    die("Connection failed: " . $link->connect_error);
}

// ตั้งค่าการเข้ารหัสเป็น UTF-8
$link->set_charset("utf8");

// ดึงข้อมูลจากตาราง t2
$sql = "SELECT stkcod FROM t2 LIMIT 10";
$result = $link->query($sql);

if (!$result) {
    die("Query failed: " . $link->error);
}

$barcodes = [];
while ($row = $result->fetch_assoc()) {
    $barcodes[] = $row['stkcod'];
}

$link->close();
?>

<!DOCTYPE html>
<html lang="th">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Generate Barcodes</title>
    <style>
        .barcode {
            margin: 10px;
            display: inline-block;
        }
    </style>
</head>
<body>
    <h1>Generated Barcodes</h1>
    <div id="barcodes">
        <?php
        $generator = new BarcodeGeneratorHTML();
        foreach ($barcodes as $barcode) {
            echo '<div class="barcode">' . $generator->getBarcode($barcode, $generator::TYPE_CODE_39) . '</div>';
        }
        ?>
    </div>
</body>
</html>