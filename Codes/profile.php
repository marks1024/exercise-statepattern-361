<?php 
	session_start(); 

	if (!isset($_SESSION['Email'])) {
		$_SESSION['msg'] = "You must log in first";
		header('location: login.php');
	}

	if (isset($_GET['logout'])) {
		session_destroy();
		unset($_SESSION['Email']);
		header("location: login.php");
	}

?>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><?php echo $title; ?></title>
        <link rel="stylesheet" type="text/css" href="Styles/Stylesheet.css" />
    </head>
    <body>
        <div class="header">
<!--		<h2>Home Page</h2>-->
	</div>
	<div class="content">

		<!-- notification message -->
		<?php if (isset($_SESSION['success'])) : ?>
			<div class="error success" >
				<h3>
					<?php 
						echo $_SESSION['success']; 
						unset($_SESSION['success']);
					?>
				</h3>
			</div>
		<?php endif ?>

		<!-- logged in user information -->
		
	</div>
        
        <div id="wrapper">
            <div id="banner">  
                <?php  if (isset($_SESSION['Email'])) : ?>
			<p>Welcome <strong><?php echo $_SESSION['Email']; ?></strong></p>
			<p> <a href="userHome.php?logout='1'" style="color: red;">logout</a> </p>
		<?php endif ?>
            </div>
            
            <nav id="navigation">
                <ul id="nav">
                    <li><a href="index.php">Home</a></li>
                    <li><a href="canteen.php">ManageCanteen</a></li>
                    <li><a href="">     </a></li>
                    <li><a href="profile.php">About</a></li>
                </ul>
            </nav>
            
            <div id="content_area">
                <?php include('server.php'); ?>

    <head>
        <title>User registration system</title>
        <link rel = "stylesheet" type ="text/css" href="style.css">
     </head>
        <body>
            <div class="header">
                <h2>Register</h2>
            </div>
            <form method = "post" action = "register.php">
                <!-- display validation errors here-->
                <?php include('errors.php')?>
                <div class = "input-group">
                    <label>First Name</label>
                    <input type="text" name ="FName" value ="<?php echo $FName; ?>">
                </div>
                <div class = "input-group">
                    <label>Last Name</label>
                    <input type="text" name ="LName" value ="<?php echo $LName; ?>">
                </div>
                <div class = "input-group">
                    <label>Email</label>
                    <input type="email" name ="Email" value ="<?php echo $Email; ?>">
                </div>
                <div class = "input-group">
                    <label>CanteenID</label>
                    <input type="text" name ="CanteenID" value ="<?php echo $CanteenID; ?>">
                </div>
                <div class = "input-group">
                    <label>Password</label>
                    <input type="password" name ="password_1">
                </div>
                <div class = "input-group">
                    <label>Confirm Password</label>
                    <input type="password" name ="password_2">
                </div>
                <div class = "input-group">
                    <button type = "submit" name = "reg_user" class = "btn">Register</button>
                </div>
                <p>
                    Already a member? <a href="login.php">Sign in</a>
                </p>
            </form>
                                                     
        </body>
 

            </div>
            
            <div id="sidebar">
                
            </div>
            
            <footer>
                <p>All rights reserved</p>
            </footer>
        </div>
    </body>
</html>

