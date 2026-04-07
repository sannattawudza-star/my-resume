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

$esp_list = ["ESP1"]; // Example list of ESPs

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    header("Content-Type: application/json; charset=UTF-8");
    $input = json_decode(file_get_contents('php://input'), true);
    $epaperIp = $input['epaperIp'];
    $data = $input['data'];

    // Save the status data to a session
    session_start();
    $_SESSION['status_data'] = $data;

    echo json_encode(['status' => 'success', 'epaperIp' => $epaperIp, 'data' => $data]);
    exit;
}

if (isset($_GET['esp'])) {
    header("Content-Type: application/json; charset=UTF-8");
    session_start();

    if (isset($_SESSION['status_data'])) {
        $statusData = $_SESSION['status_data'];
        echo json_encode(['esp' => $_GET['esp'], 'data' => $statusData]);
    } else {
        echo json_encode(['error' => 'No product information available.']);
    }
    exit;
}
?>

<!DOCTYPE html>
<html lang="th">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="css/styles.css">
    <title>Status</title>
</head>
<body>
    <nav>
        <ul>
            <li><a href="select_product.php">Home</a></li>
            <li><a href="#">Status</a></li>
        </ul>
    </nav>
    <div class="container">
        <h2>Select ESP to view status</h2>
        <select id="espSelect" onchange="fetchESPStatus()">
            <option value="">Select ESP</option>
            <?php foreach ($esp_list as $esp): ?>
                <option value="<?php echo htmlspecialchars($esp); ?>"><?php echo htmlspecialchars($esp); ?></option>
            <?php endforeach; ?>
        </select>
        <div id="espStatus"></div>
    </div>
    <script>
    function fetchESPStatus() {
        const esp = document.getElementById('espSelect').value;
        if (esp) {
            fetch('status.php?esp=' + encodeURIComponent(esp))
            .then(response => response.json())
            .then(data => {
                if (data.error) {
                    document.getElementById('espStatus').innerText = '❌ Error: ' + data.error;
                } else {
                    displayProductInfo(data);
                }
            })
            .catch(error => {
                console.error("Fetch Error:", error);
                document.getElementById('espStatus').innerText = '❌ Fetch Error: ' + error.message;
            });
        } else {
            document.getElementById('espStatus').innerText = '';
        }
    }

    function displayProductInfo(data) {
        const espStatus = document.getElementById('espStatus');
        if (data.data) {
            espStatus.innerHTML = `
                <div class="product-info">
                    <p><strong>Stock Code:</strong> ${data.data.stkcod}</p>
                    <p><strong>Description:</strong> ${data.data.description}</p>
                    <p><strong>Price:</strong> ${data.data.prc01} บาท</p>
                    <p><strong>Unit:</strong> ${data.data.primary_unit_of_measure}</p>
                    <p><strong>Date:</strong> ${data.data.chgdat}</p>
                </div>
            `;
        } else {
            espStatus.innerHTML = '<p>No product information available.</p>';
        }
    }

    // Fetch status for the first ESP on page load
    document.addEventListener('DOMContentLoaded', function() {
        const firstEsp = "<?php echo htmlspecialchars($esp_list[0]); ?>";
        document.getElementById('espSelect').value = firstEsp;
        fetchESPStatus();
    });

    // Listen for postMessage from select_product.php
    window.addEventListener('message', function(event) {
        if (event.data && event.data.type === 'updateStatus') {
            displayProductInfo(event.data);
        }
    });
    </script>
</body>
</html>