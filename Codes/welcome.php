
<!DOCTYPE html>
<html>
<body>
    
<?php
$date = '2017-11-23';
$date = strtotime($date);
echo $date;
    
$newformat = date('Y-m-d',$date);
echo $newformat;

    
date_default_timezone_set("Kazakhstan/Astana");
echo "The time is " . date("h:i:sa");
?>
    
<?php
$cars = array
  (
  array("Volvo",22,18),
  array("BMW",15,13),
  array("Saab",5,2),
  array("Land Rover",17,15)
  );
    
for ($row = 0; $row < 4; $row++) {
  echo "<p><b>Row number $row</b></p>";
  echo "<ul>";
  for ($col = 0; $col < 3; $col++) {
    echo "<li>".$cars[$row][$col]."</li>";
  }
  echo "</ul>";
}
?>

</body>
</html>