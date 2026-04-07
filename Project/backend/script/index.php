<?php 
header("Access-Control-Allow-Origin: *");

date_default_timezone_set('Asia/Bangkok');
ini_set('log_errors', 1);
ini_set('error_log', './error.log');
if($_SERVER['REQUEST_METHOD'] !== 'POST'){
    echo json_encode(array('message' => 'Method not allowed'));
    exit;
}
$folderName = date('Y-m-d');
$folderPath = '../uploads/' . $folderName; 


if (!file_exists($folderPath)) {
    mkdir($folderPath, 0777, true);
} 


$folderName1 = date('H-i-s'); 
$folderPath = '../uploads/' . $folderName . '/' . $folderName1; 

if (!file_exists($folderPath)) {
    mkdir($folderPath, 0777, true);
} 

$index = $_POST["index"];
if($index == 0){
    echo json_encode(array('message' => 'No camera selected'));
    exit;
}


$camera = [] ;
for($i = 0 ; $i < $index ; $i++){
    $camera[$i] = $_POST["camera_".$i];
    $camera[$i] = str_replace('data:image/png;base64,', '', $camera[$i]);
    $camera[$i] = base64_decode($camera[$i]);
    $filename = "camera_".$i.".png";
    $filePath = $folderPath . '/' . $filename;
    file_put_contents($filePath, $camera[$i]);
}

$command = "python index.py '$folderName' '$folderName1'";
exec($command, $output, $return_var);
echo json_encode([
    "output" => $output,
    "return_var" => $return_var,
    "error" => error_get_last()  
]);


//esp ทำตรงนี้
// $esp32_url = 'http://<ESP32_IP>/your_api_endpoint';
// $data = array(
//     'status' => 'start',
// );

// $ch = curl_init();
// curl_setopt($ch, CURLOPT_URL, $esp32_url);
// curl_setopt($ch, CURLOPT_POST, 1);
// curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($data));
// curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
// $response = curl_exec($ch);
// curl_close($ch);


?>