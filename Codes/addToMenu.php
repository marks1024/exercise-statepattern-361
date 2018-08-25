<?php  include('server.php'); ?>

<!DOCTYPE html>
<html>
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
    
    <?php $results = mysqli_query($conn, "SELECT * FROM MENU, DISH, MENU_contains_DISH WHERE DishID = DISH_DishID AND MenuID = MENU_MenuID AND MenuID = '$MenuID' order by Type"); ?>

<table>
	<thead>
		<tr>
            <th>Type</th>
			<th>Name</th>
			<th>Price</th>
			<th colspan="2">Action</th>
		</tr>
	</thead>
	
	<?php while ($row = mysqli_fetch_array($results)) { ?>
		<tr>
            <td><?php echo $row['Type']; ?></td>
			<td><?php echo $row['Name']; ?></td>
			<td><?php echo $row['Price']; ?></td>
			<td>
				<a href="home.php?edit=<?php echo $row['DishID']; ?>" class="edit_btn" >Edit</a>
			</td>
			<td>
				<a href="server.php?del=<?php echo $row['DishID']; ?>" class="del_btn">Delete</a>
			</td>
		</tr>
	<?php } ?>
</table>

	<form method="post" action="server.php" >
        <input type="hidden" name="id" value="<?php echo $id; ?>">
		<div class="input-group">
			<label>Name</label>
			<input type="text" name="Name" value="<?php echo $Name; ?>">
		</div>
        <div class="input-group">
			<label>DishID</label>
			<input type="text" name="DishID" value="<?php echo $DishID; ?>">
		</div>
         <div class="input-group">
			<label>Type</label>
			<input type="text" name="Type" value="<?php echo $Type; ?>">
		</div>
		<div class="input-group">
			<label>Price</label>
			<input type="text" name="Price" value="<?php echo $Price; ?>">
		</div>
        
		<div class="input-group">
			<?php $_SESSION['MenuID'] = $MenuID;
            if ($update == true): ?>
                <button class="btn" type="submit" name="update" style="background: #556B2F;" >update</button>
            <?php else: $_SESSION['MenuID'] = $MenuID?>
	               <button class="btn" type="submit" name="add" >Add</button>
            <?php endif ?>
            <a href="Template.php?back=" class="back_btn">Back</a>
		</div>
	</form>
</body>
</html>