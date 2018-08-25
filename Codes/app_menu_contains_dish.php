<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
$response["MENU_contains_DISH"] = array();
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// echo "Connected successfully";


$sql = "SELECT * FROM MENU_contains_DISH";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $resultArray = array();

    while($row = mysqli_fetch_assoc($result)) {
        $MENU_contains_DISH = array();
        $MENU_contains_DISH["MENU_MenuID"] = $row["MENU_MenuID"];
        $MENU_contains_DISH["DISH_DishID"] = $row["DISH_DishID"];
        array_push($response["MENU_contains_DISH"], $MENU_contains_DISH);
    }


    echo json_encode($response["MENU_contains_DISH"]);

} else {
    echo "0 results";
}

mysqli_close($conn);
?>
