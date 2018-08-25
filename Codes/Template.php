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
        <link rel="stylesheet" type="text/css" href="Stylesheet.css" />
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
                    <li><a href="">About</a></li>
                </ul>
            </nav>
            
            <div id="content_area">
                <?php echo $content; ?>
            </div>
            
            <div id="sidebar">
                
                <img src="https://i.imgur.com/MeA666P.png" class="imgLeft" style = "width:80%; height:100%;" />
                
            </div>
            
            <footer>
                <p>All rights reserved</p>
            </footer>
        </div>
    </body>
</html>
