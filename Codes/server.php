<?php

session_start();
$FName = "";
$LName = "";
$Email = "";
$CanteenID = "";
$errors = array();
$_SESSION['success'] = "";

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
//echo "Connected successfully";

if(isset($_POST['reg_user'])){
    $FName = mysqli_real_escape_string($conn, $_POST['FName']);
    $LName = mysqli_real_escape_string($conn, $_POST['LName']);
    $Email = mysqli_real_escape_string($conn, $_POST['Email']);
    $CanteenID = mysqli_real_escape_string($conn, $_POST['CanteenID']);
    $password_1 = mysqli_real_escape_string($conn, $_POST['password_1']);
    $password_2 = mysqli_real_escape_string($conn, $_POST['password_2']);
    
    if(empty($FName)){
    array_push($errors, "First Name is required");
}

if(empty($LName)){
    array_push($errors, "Last Name is required");
}
    
if(empty($Email)){
    array_push($errors, "Email is required");
}
    
    
    $checkEmail = "SELECT* FROM USER WHERE Email = '$Email'";
    $results = mysqli_query($conn, $checkEmail);
    if (mysqli_num_rows($results) == 1) {
			array_push($errors, "Email already exists");
		}

if(empty($password_1)){
    array_push($errors, "Password is required");
}

if($password_1 != $password_2){
    array_push($errors, "The two passwords do not match");
}

if(count($errors) == 0){
    
    $Password = $password_1;
    $sql = "INSERT INTO USER (Email, AdministratorFlag, ClientFlag, FName, LName, Password) VALUES ('$Email', '1', '0', '$FName', '$LName', '$Password')";
    mysqli_query($conn, $sql);
    
//    mysqli_query($conn, "INSERT INTO MENU_contains_DISH  values ('$MenuID', '$DishID')"); 
    
    $_SESSION['Email'] = $Email;
    $_SESSION['success'] = "You are now logged in";
    header('location: Template.php');
}
}

if(isset($_POST['login_user'])){
    $Email = mysqli_real_escape_string($conn, $_POST['Email']);
    $Password = mysqli_real_escape_string($conn, $_POST['Password']);
   
    if(empty($Email)){
        array_push($errors, "Email is required");
    }

    if(empty($Password)){
        array_push($errors, "Password is required");
    }
    
    if(count($errors) == 0){
    //$Password = md5(Password);
    $sql = "SELECT* FROM USER WHERE Email = '$Email' AND Password ='$Password'";
    $results = mysqli_query($conn, $sql);
    
    if(mysqli_num_rows($results) == 1){
        //log in
        $_SESSION['Email'] = $Email;
        $_SESSION['success'] = "You are now logged in";
        header('location: index.php');
    }else{
        array_push($errors, "Wrong email/password combination");
    }
    }
}

if (isset($_POST['save'])) {
        $Name = "";
	    $Price = 0;
	    $update = false;
        $add = false;
		$Name = $_POST['Name'];
        $DishID = $_POST['DishID'];
		$Price = (int)$_POST['Price'];
        $Type = $_POST['Type'];

		mysqli_query($conn, "INSERT INTO DISH (Name, Price, DishID, Type) VALUES ('$Name', '$Price', '$DishID', '$Type')"); 
        $MenuID = $_SESSION['MenuID'];
        mysqli_query($conn, "INSERT INTO MENU_contains_DISH  values ('$MenuID', '$DishID')"); 
        
		$_SESSION['message'] = "Dish saved"; 
		header('location: '. $_SERVER['HTTP_REFERER']);
	}

if (isset($_POST['add'])) {
        $Name = "";
	    $Price = 0;
	    $add = false;
		$Name = $_POST['Name'];
        $DishID = $_POST['DishID'];
		$Price = (int)$_POST['Price'];
        $Type = $_POST['Type'];
        $MenuID = $_POST['MenuID'];

        //$MenuID = $_SESSION['MenuID'];
    
        mysqli_query($conn, "INSERT INTO MENU_contains_DISH  values ('$MenuID', '$DishID')"); 
        
		$_SESSION['message'] = "Dish added"; 
		header('location: ' . $_SERVER['HTTP_REFERER']);
	}


if (isset($_POST['update'])) {
	$DishID = $_POST['DishID'];
	$Name = $_POST['Name'];
	$Price = (int)$_POST['Price'];
    $Type = $_POST['Type'];

	mysqli_query($conn, "UPDATE DISH SET Name='$Name', Price='$Price', Type = '$Type' WHERE DishID='$DishID'");
	$_SESSION['message'] = "Dish updated!"; 
	header('location: menu.php');
}

if(isset($_GET['del'])){
    $DishID = $_GET['del'];
    mysqli_query($conn, "DELETE FROM MENU_contains_DISH WHERE DISH_DishID ='$DishID'");
    $_SESSION['message'] = "Dish deleted!";
    header('location: '. $_SERVER['HTTP_REFERER']);
}

	if (isset($_GET['edit'])) {
		$DishID = $_GET['edit'];
		$update = true;
        
		$record = mysqli_query($conn, "SELECT * FROM DISH WHERE DishID = '$DishID'");

		if (count($record) == 1) {
			$n = mysqli_fetch_array($record);
			$Name = $n['Name'];
			$Price = $n['Price'];
            $Type = $n['Type'];
		}
	}


if (isset($_POST['Save'])) {
        $CName = "";
        $Location = "";
        $Description = "";
        $Timeslot = "";
	    $Capacity = 0;
	    $Update = false;
		$CanteenID = $_POST['CanteenID'];
        $CName = $_POST['CName'];
        $Location = $_POST['Location'];
        $Description = $_POST['Description'];
	    $Capacity = (int)$_POST['Capacity'];
        $Timeslot = $_POST['Timeslot'];
        $Admin_Email = $_SESSION['Email'];
      

		mysqli_query($conn, "INSERT INTO CANTEEN (CName, Location, Description, Capacity, Admin_Email, CanteenID, Timeslot) VALUES ('$CName', '$Location', '$Description', '$Capacity', '$Admin_Email', '$CanteenID', '$Timeslot')"); 
		$_SESSION['message'] = "Canteen saved"; 
		header('location: '. $_SERVER['HTTP_REFERER']);
	}

if (isset($_POST['Update'])) {
	$CanteenID = $_POST['CanteenID'];
	$CName = $_POST['CName'];
    $Location = $_POST['Location'];
    $Description = $_POST['Description'];
	$Capacity = (int)$_POST['Capacity'];
    $Timeslot = $_POST['Timeslot'];

	mysqli_query($conn, "UPDATE CANTEEN SET CName='$CName', CanteenID='$CanteenID', Location='$Location', Description='$Description', Capacity='$Capacity', Timeslot = '$Timeslot' WHERE CanteenID='$CanteenID'");
	$_SESSION['message'] = "Canteen updated!"; 
	header('location: '. $_SERVER['HTTP_REFERER']);
}

if(isset($_GET['delc'])){
    $CanteenID = $_GET['delc'];
    mysqli_query($conn, "DELETE FROM CANTEEN WHERE CanteenID='$CanteenID'");
    $_SESSION['message'] = "Canteen deleted!";
    header('location: canteen.php');
}

	if (isset($_GET['editc'])) {
		$CanteenID = $_GET['editc'];
		$Update = true;
        
		$record = mysqli_query($conn, "SELECT * FROM CANTEEN WHERE CanteenID = '$CanteenID'");

		if (count($record) == 1) {
			$n = mysqli_fetch_array($record);
			$CName = $n['CName'];
            $CanteenID = $n['CanteenID'];
            $Location = $n['Location'];
            $Description = $n['Description'];
	        $Capacity = $n['Capacity'];
            $Timeslot = $n['Timeslot'];
		}
	}

//if(isset($_GET['back'])){
//    header('location: index.php');
//}

if (isset($_POST['saveMenu'])) {

	    $upDate = false;
        $MenuID = $_POST['MenuID'];
        $Date = $_POST['Date'];
        $Daytime = $_POST['Daytime'];

		mysqli_query($conn, "INSERT INTO MENU VALUES ('$MenuID', '$Daytime', '$Date')"); 
    
        $CanteenID = $_SESSION['CanteenID'];
    
        mysqli_query($conn, "INSERT INTO CANTEEN_offers_MENU  values ('$CanteenID', '$MenuID')"); 
    
		$_SESSION['message'] = "Menu saved"; 
		header('location: ' . $_SERVER['HTTP_REFERER']);
	}



if (isset($_POST['updateMenu'])) {
	$MenuID = $_POST['MenuID'];
	$Date = $_POST['Date'];
    $Daytime = $_POST['Daytime'];

	mysqli_query($conn, "UPDATE MENU SET Date='$Date', Daytime = '$Daytime' WHERE MenuID='$MenuID'");
	$_SESSION['message'] = "Menu updated!"; 
	header('location: canteen.php');
}

if(isset($_GET['delm'])){
    $MenuID = $_GET['delm'];
    mysqli_query($conn, "DELETE FROM MENU WHERE MenuID='$MenuID'");
    $_SESSION['message'] = "Menu deleted!";
    header('location: '. $_SERVER['HTTP_REFERER']);
}

	if (isset($_GET['editm'])) {
		$MenuID = $_GET['editm'];
		$upDate = true;
        
		$record = mysqli_query($conn, "SELECT * FROM MENU WHERE MenuID = '$MenuID'");

		if (count($record) == 1) {
			$n = mysqli_fetch_array($record);
            $MenuID = $n['MenuID'];
			$Date = $n['Date'];
            $Daytime = $n['Daytime'];
            
		}
	}

if(isset($_GET['search'])){
    $add = true;
    $q = $_GET['q'];
//    echo $q;
    if($q =='Search...'){
        header('Location: home.php');
    }
    if($q != ''){
        if(!isset($q)){
            echo '';
        }else{
            $query = mysqli_query($conn, "SELECT * FROM DISH WHERE Type LIKE '%$q%' OR Name LIKE '%$q%'");
            $num_rows = mysqli_num_rows($query);
            // header('Location: addToMenu.php');
            echo '<p><strong>'.$num_rows.'</strong> results for'.$q_value.'</p>';
            while ($row = mysqli_fetch_array($query)){
                $DishID = $row['DishID'];
                $Type = $row['Type'];
                $Name = $row['Name']; 
			    $Price = $row['Price'];
                $MenuID = $_SESSION['MenuID'];
                $add = true;
                echo ' '.$Type.' '.$Name.' '.$Price.' '.$MenuID.'<br/>';
            }
        }
        }else{
             header('Location: home.php');
        }   
    }

?>


























    