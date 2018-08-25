<?php    
    
include "connection.php";    
    
//if(isset($_GET['id'])){    
//$sql = "delete from registration where id = '".$_GET['id']."'";    
//$result = mysql_query($sql);    
//}    
    
$sql = "select * from USER";    
$result = mysql_query($sql);    
?>    
<html>    
    <body>    
        <table width = "100%" border = "1" cellspacing = "1" cellpadding = "1">    
            <tr> 
                <td>Email</td>   
                <td>AdministratorFlag</td>    
                <td>ClientFlag</td> 
                <td>Fname</td>    
                <td>LName</td>  
                <td>Password</td>    
                <td>Confirm Password</td>         
                <td colspan = "2">Action</td>    
            </tr>    
        </table>    
    </body>    
</html>  