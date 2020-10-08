<?php

$API_KEY = "ed03df8b"; // API key (string) provided by Open Movie DataBase (i.e., "ab123456")

session_start(); // Connect to the existing session

processPageRequest(); // Call the processPageRequest() function

// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE ABOVE THIS LINE

function displaySearchForm()
{
	require_once './templates/search_form.html';
}

function displaySearchResults($searchString)
{
    $results = file_get_contents('http://www.omdbapi.com/?apikey='.$GLOBALS['API_KEY'].'&s='.urlencode($searchString).'&type=movie&r=json');
    $resultsArray = json_decode($results, true)["Search"];
    require_once './templates/results_form.html';
}

function processPageRequest()
{
    if (isset($_SESSION['displayName']) && !empty($_SESSION['displayName']))
    {
        if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['Keyword'])) {
            displaySearchResults($_POST['Keyword']);
        }
        else{displaySearchForm();}
    }
    else
        {
            header("Location: ./logon.php");
            exit;
        }
}
?>