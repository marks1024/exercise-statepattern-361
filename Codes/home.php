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
    <link rel="stylesheet" type="text/css" href="menuStyle.css">
       <script type = "text/javascript">
            function active(){
                var searchBar = document.getElementById('searchBar');
                
                if(searchBar.value == 'Search...'){
                    searchBar.value = ''
                    searchBar.placeholder = 'Search...'
                }
            }
            
             function inactive(){
                var searchBar = document.getElementById('searchBar');
                
                if(searchBar.value == ''){
                    searchBar.value = 'Search...'
                    searchBar.placeholder = 'Search...'
                }
            }
        </script>
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
     <form action="home.php" method="GET" id = "searchForm" >
         <div class="input-group">
            <input type = "text" name = "q" id="searchBar"  placeholder ="" value="Search..." maxlength="25" autocomplete="off" onMouseDown="active();" onBlur="inactive();" style = "right-border: none" /><input type="submit" name = "search" id="searchBtn"  value="Go!" style = "  border: 1px solid #000000;
    font-size: 18px;
    padding: 14px 10px 35px 10px; width: 60px; hight: 80px; left-border: none; "/>
         </div>
        </form>

    
	<form method="post" action="server.php" >
        <input type="hidden" name="MenuID" value="<?php echo $MenuID; ?>">
        <input type="hidden" name="CanteenID" value="<?php echo $CanteenID; ?>">
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
            <?php elseif($add == true): $_SESSION['MenuID'] = $MenuID?>
	               <button class="btn" type="submit" name="add" >Add</button>
            <?php else: $_SESSION['MenuID'] = $MenuID?>
	               <button class="btn" type="submit" name="save" >Save</button>
            <?php endif ?>
            <div style = "text-align: right">
                
                <a href="canteen.php" class="back_btn">Back</a>
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

