<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
$response["CANTEEN_offers_MENU"] = array();
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// echo "Connected successfully";


$sql = "SELECT * FROM CANTEEN_offers_MENU";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $resultArray = array();

    while($row = mysqli_fetch_assoc($result)) {
        $CANTEEN_offers_MENU = array();
        $CANTEEN_offers_MENU["CANTEEN_CanteenID"] = $row["CANTEEN_CanteenID"];
        $CANTEEN_offers_MENU["MENU_MenuID"] = $row["MENU_MenuID"];
        array_push($response["CANTEEN_offers_MENU"], $CANTEEN_offers_MENU);
    }


    echo json_encode($response["CANTEEN_offers_MENU"]);

} else {
    echo "0 results";
}

mysqli_close($conn);
?>
