<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
$response["DISH"] = array();
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// echo "Connected successfully";


$sql = "SELECT * FROM DISH";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $resultArray = array();


    while($row = mysqli_fetch_assoc($result)) {

        $DISH = array();
        $DISH["Name"] = $row["Name"];
//        $DISH["Portion"] = $row["Portion"];

        $DISH["Price"] = (String)($row["Price"]);
        $DISH["Description"] = $row["Description"];
        $DISH["DishID"] = $row["DishID"];
        array_push($response["DISH"], $DISH);
//
//        $tempArray = array();
//        $tempArray = $row["Name"];
//        $tempArray = $row["Portion"];
//        $tempArray = $row["Price"];
//        $tempArray = $row["Description"];
//        $tempArray = $row["DishID"];
//        array_push($resultArray, $tempArray);
    }


    echo json_encode($response["DISH"]);

} else {
    echo "0 results";
}

mysqli_close($conn);
?>
