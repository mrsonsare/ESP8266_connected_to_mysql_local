

<?php

echo "       HEY BABY SHAKALAKA BOOM-BOOM<br>";
 
    $host = "localhost";		         // host = localhost because database hosted on the same server where PHP files are hosted
    $dbname = "iotdazzer";              // Database name
    $username = "xyxt";		// Database username
    $password = "5R(!e4yEc]THcP-@";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. "; }

   
// // Get date and time variables
//     date_default_timezone_set('Asia/Kolkata');  
//     $d = date("Y-m-d");
//     $t = date("H:i:s");
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['sendval']) )
    {
		$val = $_POST['sendval'];
            


// Update your tablename here
	        $sql = "INSERT INTO iot (sensor,location,value1) VALUES ('mysensor','xyz','".$val."')"; 
 


		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();



?>