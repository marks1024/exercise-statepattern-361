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
<!--    <h1>Manage Your Canteen</h1>-->
	<title>CRUD: CReate, Update, Delete PHP MySQL canteen</title>
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
    
    <?php 
    $Admin_Email = $_SESSION['Email'];
    $results = mysqli_query($conn, "SELECT * FROM CANTEEN WHERE Admin_Email = '$Admin_Email'"); ?>

<table>
	<thead>
		<tr>
            <th>       </th>
            <th>Canteen</th>
			<th>Location</th>
			<th>Description</th>
            <th>Capacity</th>
			<th>Timeslot</th>
			<th colspan="2">Action</th>
		</tr>
	</thead>
	
	<?php while ($row = mysqli_fetch_array($results)) { ?>
		<tr>
            <td>
				<a href="menu.php?editc=<?php echo $row['CanteenID']; ?>" class="edit_btn" >Menu</a>
			</td>
            <td><?php echo $row['CName']; ?></td>
			<td><?php echo $row['Location']; ?></td>
			<td><?php echo $row['Description']; ?></td>
            <td><?php echo $row['Capacity']; ?></td>
            <td><?php echo $row['Timeslot']; ?></td>
			<td>
				<a href="canteen.php?editc=<?php echo $row['CanteenID']; ?>" class="edit_btn" >Edit</a>
			</td>
			<td>
				<a href="server.php?delc=<?php echo $row['CanteenID']; ?>" class="del_btn">Delete</a>
			</td>
		</tr>
	<?php } ?>
</table>
    
	<form method="post" action="server.php" >
		<div class="input-group">
			<label>CanteenName</label>
			<input type="text" name="CName" value="<?php echo $CName; ?>">
		</div>
        <div class="input-group">
			<label>CanteenID</label>
			<input type="text" name="CanteenID" value="<?php echo $CanteenID; ?>">
		</div>
         <div class="input-group">
			<label>Description</label>
			<input type="text" name="Description" value="<?php echo $Description; ?>">
		</div>
		<div class="input-group">
			<label>Location</label>
			<input type="text" name="Location" value="<?php echo $Location; ?>">
		</div>
        <div class="input-group">
			<label>Capacity</label>
			<input type="text" name="Capacity" value="<?php echo $Capacity; ?>">
		</div>
         <div class="input-group">
			<label>Timeslot</label>
			<input type="text" name="Timeslot" value="<?php echo $Timeslot; ?>">
		</div>
		<div class="input-group">
			<?php if ($Update == true): ?>
                <button class="btn" type="submit" name="Update" style="background: #556B2F;" >update</button>
            <?php else: ?>
	               <button class="btn" type="submit" name="Save" >save</button>
            <?php endif ?>
            <div style = "text-align: right">
                <a href="index.php?back=" class="back_btn">Back</a>
            </div>
		</div>
            
	</form>
</body>

            </div>
            
<!--
            <div id="sidebar">
            <img src="https://www.chestnutasheville.com/wp-content/uploads/2016/09/menu-icon.jpg" class="imgLeft" />

            </div>
-->
            
            <footer>
                <p>All rights reserved</p>
            </footer>
        </div>
    </body>
</html>


