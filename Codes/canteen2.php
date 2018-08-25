<?php  include('server.php'); 
$title = "Home";
$content = "
<!DOCTYPE html>
<html>
<head>
    <h1>Manage Your Canteen</h1>
	<title>CRUD: CReate, Update, Delete PHP MySQL canteen</title>
    <link rel="stylesheet" type="text/css" href="menuStyle.css">
</head>
<body>"
     if (isset($_SESSION['message'])): 
$content = $content + "
	<div class="msg">"
		
			echo $_SESSION['message']; 
			unset($_SESSION['message']);
		
$content = $content + "	</div>"
 php endif 
    
    $Admin_Email = $_SESSION['Email'];
    $results = mysqli_query($conn, "SELECT * FROM CANTEEN WHERE Admin_Email = '$Admin_Email'");

$content = $content + "
<table>
	<thead>
		<tr>
            <th>Canteen</th>
			<th>Location</th>
			<th>Description</th>
            <th>Capacity</th>
			<th>Timeslot</th>
			<th colspan="2">Action</th>
		</tr>
	</thead>"
	
    while ($row = mysqli_fetch_array($results)) { 
    $content = $content + "<tr>
            <td><?php echo $row['CName']; ?></td>
			<td><?php echo $row['Location']; ?></td>
			<td><?php echo $row['Description']; ?></td>
            <td><?php echo $row['Capacity']; ?></td>
            <td><?php echo $row['Timeslot']; ?></td>
			<td>"
				<a href="canteen.php?editc= echo $row['CanteenID'];" class="edit_btn" >Edit</a>
			</td>
			<td>
				<a href="server.php?delc=echo $row['CanteenID'];" class="del_btn">Delete</a>
			</td>
		</tr>
	 } 
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
		</div>
        <a href="Template.php?back=" class="back_btn">Back</a>
	</form>
</body>
</html>

 include 'Template.php';?>