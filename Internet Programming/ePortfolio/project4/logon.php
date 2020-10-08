<?php

$EMAIL_ID = 369293558; // 9-digit integer value (i.e., 123456789)

require_once '/home/common/php/dbInterface.php'; // Add database functionality
require_once '/home/common/php/mail.php'; // Add email functionality
require_once '/home/common/php/p4Functions.php'; // Add Project 4 base functions

processPageRequest(); // Call the processPageRequest() function

// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE ABOVE THIS LINE

function authenticateUser($username, $password) 
{
	$arr = validateUser($username, $password);
	if ($arr === null)
	{
		return false;
	}
	else
	{
	    session_start();
	    $_SESSION["userId"] = $arr[0];
        $_SESSION["displayName"] = $arr[1];
        $_SESSION["emailAddress"] = $arr[2];
        return true;
	}
}

function displayLoginForm($message = "")
{
	require_once './templates/logon_form.html';
}

function processPageRequest()
{
	// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE BELOW THIS LINE
	if(session_status() == PHP_SESSION_ACTIVE)
	{
		session_destroy();
	}
	// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE ABOVE THIS LINE
	if ($_SERVER['REQUEST_METHOD'] == 'POST'){
		$Username = $_POST['Username'];
		$Password = $_POST['Password'];

		if (authenticateUser($Username, $Password)){
			header("Location: ./index.php");
			exit;
		}
		else{displayLoginForm($message = "Incorrect Login Information");}
	}
	else{displayLoginForm();}
}
?>
