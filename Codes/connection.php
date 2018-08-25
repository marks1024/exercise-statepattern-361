<!DOCTYPE html>
<html>
    <body>
<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
echo "Connected successfully";

//    $response["USER"] = array();
//$sql = "SELECT * FROM USER";
//$result = mysqli_query($conn, $sql);
//
//if (mysqli_num_rows($result) > 0) {
//    // output data of each row
//    $resultArray = array();
//	
//    
//    while($row = mysqli_fetch_assoc($result)) {
//        
//        $DISH = array();
//        $DISH["Email"] = $row["Email"];
//        $DISH["AdministratorFlag"] = $row["AdministratorFlag"];
//        $DISH["ClientFlag"] = $row["ClientFlag"];
//        $DISH["FName"] = $row["FName"];
//        $DISH["LName"] = $row["LName"];
//        $DISH["Password"] = $row["Password"];
//        array_push($response["USER"], $DISH);
//
//    }
//    
//    
//    echo json_encode($response["USER"]);
//    
//} else {
//    echo "0 results";
//}
mysqli_close($conn);
?>
        </body>
</html>