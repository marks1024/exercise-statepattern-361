<?php
$servername = "127.0.0.1";
$username = "root";
$password = "23112017cp";
$dbname = "mydb";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
$response["CANTEEN"] = array();
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// echo "Connected successfully";


$sql = "SELECT * FROM CANTEEN";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $resultArray = array();

    while($row = mysqli_fetch_assoc($result)) {
        $CANTEEN = array();
        $CANTEEN["CanteenID"] = $row["CanteenID"];
        $CANTEEN["Description"] = $row["Description"];
        $CANTEEN["Location"] = $row["Location"];
        $CANTEEN["Capacity"] = $row["Capacity"];
        $CANTEEN["Admin_Email"] = $row["Admin_Email"];
        $CANTEEN["CName"] = $row["CName"];
        $CANTEEN["Timeslot"] = $row["Timeslot"];
        array_push($response["CANTEEN"], $CANTEEN);
    }


    echo json_encode($response["CANTEEN"]);

} else {
    echo "0 results";
}

mysqli_close($conn);
?>
