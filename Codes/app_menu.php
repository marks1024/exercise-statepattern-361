<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
$response["MENU"] = array();
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// echo "Connected successfully";


$sql = "SELECT * FROM MENU";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $resultArray = array();

    while($row = mysqli_fetch_assoc($result)) {
        $MENU = array();
        $MENU["MenuID"] = $row["MenuID"];
        $MENU["Date"] = (String)$row["Date"];
        array_push($response["MENU"], $MENU);
    }


    echo json_encode($response["MENU"]);

} else {
    echo "0 results";
}

mysqli_close($conn);
?>
