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
                <?php  include('server.php'); ?>

<head>
	<title>CRUD: CReate, Update, Delete PHP MySQL dishes</title>
    <link rel="stylesheet" type="text/css" href="menuStyle.css">
</head>
<body>
    <?php if (isset($_SESSION['message'])): ?>
	<div class="msg">
		<?php 
			echo $_SESSION['message']; 
			unset($_SESSION['message']);
		?>
	</div>
 <?php endif ?>
    
    <?php $results = mysqli_query($conn, "SELECT * FROM MENU, CANTEEN, CANTEEN_offers_MENU WHERE CanteenID = CANTEEN_CanteenID AND MenuID = MENU_MenuID AND CanteenID = '$CanteenID' order by Daytime"); ?>

<table>
	<thead>
		<tr>
            <th>      </th>
            <th>MenuID</th>
            <th>Daytime</th>
			<th>Date</th>
			<th colspan="2">Action</th>
		</tr>
	</thead>
	
	<?php while ($row = mysqli_fetch_array($results)) { ?>
		<tr>
            <td>
				<a href="home.php?editm=<?php echo $row['MenuID']; ?>" class="edit_btn" >Show</a>
			</td>
            <td><?php echo $row['MenuID']; ?></td>
            <td><?php echo $row['Daytime']; ?></td>
			<td><?php echo $row['Date']; ?></td>
			<td>
				<a href="menu.php?editm=<?php echo $row['MenuID']; ?>" class="edit_btn" >Edit</a>
			</td>
			<td>
				<a href="server.php?delm=<?php echo $row['MenuID']; ?>" class="del_btn">Delete</a>
			</td>
		</tr>
	<?php } ?>
</table>

    
	<form method="post" action="server.php" >
        <div class="input-group">
			<label>MenuID</label>
			<input type="text" name="MenuID" value="<?php echo $MenuID; ?>">
		</div>
        <div class="input-group">
			<label>Daytime</label>
			<input type="text" name="Daytime" value="<?php echo $Daytime; ?>">
		</div>
        <div class="input-group">
			<label>Date</label>
			<input type="text" name="Date" value="<?php echo $Date; ?>">
		</div>
		<div class="input-group">
			<?php $_SESSION['CanteenID'] = $CanteenID;
            if ($upDate == true): ?>
                <button class="btn" type="submit" name="updateMenu" style="background: #556B2F;" >update</button>
            <?php else: ?>
	               <button class="btn" type="submit" name="saveMenu" >Save</button>
            <?php endif ?>
            <div style = "text-align: right">
            <a href="canteen.php?back=" class="back_btn" >Back</a>
            </div>
		</div>
	</form>
</body>

            </div>

            <footer>
                <p>All rights reserved</p>
            </footer>
        </div>
    </body>
</html>

