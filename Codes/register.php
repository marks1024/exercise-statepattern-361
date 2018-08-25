<?php include('server.php'); ?>
<!DOCTYPE html>
<html>
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

</html>  
