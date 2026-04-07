<?php
$link = mysqli_connect('127.0.0.1', 'root', '', 'price01'); // เปลี่ยนชื่อของฐานข้อมูลเป็น 'price01'
mysqli_set_charset($link, 'utf8');

if (!$link) {
    die("Connection failed: " . mysqli_connect_error());
}
?>