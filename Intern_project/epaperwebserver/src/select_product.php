<?php
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

// กำหนดจำนวนสินค้าต่อหน้า
$items_per_page = 10;
$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
$offset = ($page - 1) * $items_per_page;

// ดึงข้อมูลจากตาราง t2
$sql = "SELECT row_id, description, prc01, primary_unit_of_measure, chgdat FROM t2 LIMIT $items_per_page OFFSET $offset";
$result = $link->query($sql);

if (!$result) {
    die("Query failed: " . $link->error);
}

// นับจำนวนสินค้าทั้งหมด
$total_items_sql = "SELECT COUNT(*) as count FROM t2";
$total_items_result = $link->query($total_items_sql);
$total_items = $total_items_result->fetch_assoc()['count'];
$total_pages = ceil($total_items / $items_per_page);

if (isset($_GET['custom_text'])) {
    header('Content-Type: application/json');
    $custom_text = $_GET['custom_text'];
    $stmt = $link->prepare("SELECT row_id, description, prc01, primary_unit_of_measure, chgdat, stkcod FROM t2 WHERE stkcod = ?");
    $stmt->bind_param("s", $custom_text);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        echo json_encode($row);
    } else {
        echo json_encode(['error' => 'No matching product found']);
    }
    $stmt->close();
    exit;
}
?>

<!DOCTYPE html>
<html lang="th">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="css/styles.css">
    <style>
        h2 {
            font-size: 1.5rem;
            color: #333;
            margin-bottom: 10px;
            text-align: left;
        }

        input[type="text"] {
            width: 100%;
            padding: 10px;
            margin: 10px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 1rem;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 1rem;
            transition: background-color 0.3s ease;
        }

        button:hover {
            background-color: #45a049;
        }

        .input-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f9f9f9;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        .input-group {
            margin-bottom: 20px;
        }
    </style>
</head>
<body>
    <nav>
        <ul>
            <li><a href="status.php">Status</a></li>
        </ul>
    </nav>
    <div class="container">
        <div class="input-container">
            <div class="input-group">
                <h2>Product</h2>
                <input type="text" id="customInput" placeholder="Enter Product Barcode">
            </div>
            <div class="input-group">
                <h2>Epaper</h2>
                <input type="text" id="epaperInput" placeholder="Enter Epaper IP">
            </div>
            <button id="sendButton" onclick="sendCustomText()">Send</button>
        </div>
    </div>
    <script>
    function sendToEPaper(productId, epaperIp, primaryUnitOfMeasure, stkcod) {
        fetch('http://' + epaperIp + '/?product_id=' + productId + '&primary_unit_of_measure=' + encodeURIComponent(primaryUnitOfMeasure) + '&stkcod=' + encodeURIComponent(stkcod), { // Use the entered IP for the fetch request
            method: 'GET',
            mode: 'no-cors' // Add this line to disable CORS
        })
        .then(response => {
            console.log("Response Status:", response.status); // Log the response status
            return response.text(); // ใช้ .text() เพื่อ Debug
        })
        .then(text => {
            console.log("Raw Response:", text); // ✅ Debug response
            // ลบการแจ้งเตือน JSON Parse Error
        })
        .catch(error => {
            console.error("Fetch Error:", error);
            if (error.message.includes('Failed to fetch')) {
                alert('❌ Network Error: Failed to connect to the server. Please check the server status and your network connection.');
            } else {
                alert('❌ Fetch Error: ' + error.message);
            }
        });
    }

    function sendCustomText() {
        const customText = document.getElementById('customInput').value;
        const epaperIp = document.getElementById('epaperInput').value;
        fetch('select_product.php?custom_text=' + encodeURIComponent(customText))
        .then(response => response.json())
        .then(data => {
            if (data.error) {
                alert('❌ Error: ' + data.error);
            } else {
                sendToEPaper(data.row_id, epaperIp, data.primary_unit_of_measure, data.stkcod);
                updateStatusPage(epaperIp, data); // อัปเดตหน้า status ด้วยข้อมูลสินค้า
                // รีเซ็ตค่าใน text box
                document.getElementById('customInput').value = '';
                document.getElementById('epaperInput').value = '';
            }
        })
        .catch(error => {
            console.error("Fetch Error:", error);
            alert('❌ Fetch Error: ' + error.message);
        });
    }

    function updateStatusPage(epaperIp, data) {
        fetch('status.php', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ epaperIp: epaperIp, data: data })
        })
        .then(response => response.json())
        .then(statusData => {
            if (statusData.error) {
                alert('❌ Error updating status: ' + statusData.error);
            } else {
                console.log('Status updated successfully');
            }
        })
        .catch(error => {
            console.error("Status Update Error:", error);
            alert('❌ Status Update Error: ' + error.message);
        });
    }
    </script>
    <div id="productInfo"></div>
</body>
</html>