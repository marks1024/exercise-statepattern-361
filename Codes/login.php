<?php include('server.php') ?>

<!DOCTYPE html>
<html>
    <head>
        <title>User registration system</title>
        <link rel = "stylesheet" type ="text/css" href="style.css">
     </head>
        <body>
            <div class="header">
                <h2>Login</h2>
            </div>
            <form method = "post" action = "login.php">
                <?php include('errors.php'); ?>
                <div class = "input-group">
                    <label>Email</label>
                    <input type="text" name ="Email">  
                </div>
                <div class = "input-group">
                    <label>Password</label>
                    <input type="Password" name ="Password">
                </div>
                <div class = "input-group">
                    <button type = "submit" name = "login_user" class = "btn">Login</button>
                </div>
                <p>
                    Not yet a member? <a href="register.php">    Sign up</a>
                </p>
            </form>
                               
                               
        </body>

</html>  
