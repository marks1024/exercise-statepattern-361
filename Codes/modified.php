<?php 

include "connection.php"; 

//if (!isset($_POST['Email']) || !isset($_POST['AdministratorFlag']) || !isset($_POST['ClientFlag']) || !isset($_POST['FName']) || !isset($_POST['LName']) || !isset($_POST['Password']) || $_POST['Email']=='' || $_POST['AdministratorFlag']=='' || $_POST['ClientFlag']=='' || $_POST['FName']=='' || $_POST['LName']=='' || $_POST['Password']==''){
//    //header('Location: http://localhost');
//    die();
//}

$counter=0;
$Email=$_POST['Email'];
//$AdministratorFlag=$_POST['AdministratorFlag'];
//$ClientFlag=$_POST['ClientFlag'];
$FName=$_POST['FName'];
$LName=$_POST['LName'];
$Password=$_POST['Password'];

$sql = "INSERT INTO list (`Email`, `FName`, 'LName', 'Password') VALUES ('$Email', '$FName','$LName','$Password')";

 ?>  