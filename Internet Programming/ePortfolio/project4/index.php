<?php

$EMAIL_ID = 369293558; // 9-digit integer value (i.e., 123456789)
$API_KEY = "ed03df8b"; // API key (string) provided by Open Movie DataBase (i.e., "ab123456")

session_start(); // Connect to the existing session

require_once '/home/common/php/dbInterface.php'; // Add database functionality
require_once '/home/common/php/mail.php'; // Add email functionality
require_once '/home/common/php/p4Functions.php'; // Add Project 4 base functions

processPageRequest(); // Call the processPageRequest() function

// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE ABOVE THIS LINE

function addMovieToCart($imdbID)
{
    $temp = movieExistsInDB($imdbID);

    if ($temp === 0){
        $result= file_get_contents('http://www.omdbapi.com/?apikey='.$GLOBALS['API_KEY'].'&i='.$imdbID.'&type=movie&r=json');
        $movieInfo = json_decode($result, true);
        $poster = $movieInfo["Poster"];
        $title = $movieInfo["Title"];
        $year = $movieInfo["Year"];
        $imdbId = $movieInfo["imdbID"];
        $rating = $movieInfo["Rated"];
        $runtime = $movieInfo["Runtime"];
        $genre = $movieInfo["Genre"];
        $actors = $movieInfo["Actors"];
        $director = $movieInfo["Director"];
        $writer = $movieInfo["Writer"];
        $plot = $movieInfo["Plot"];
        addMovie($imdbId, $title, $year, $rating, $runtime, $genre, $actors, $director, $writer, $plot, $poster);

    }
    addMovieToShoppingCart($_SESSION['userId'], $temp);
    displayCart();
}

function displayCart()
{
    $carts = getMoviesInCart($_SESSION['userId']);
	require_once  './templates/cart_form.html';
}

function processPageRequest()
{
    if(isset($_SESSION['displayName']) && !empty($_SESSION['displayName'])) {
        if (isset($_GET['action']) && !empty($_GET['action'])){
            if ($_GET['action'] === 'add'){
                addMovieToCart($_GET['imdb_id']);
                displayCart();
            }
            else if ($_GET['action'] === 'remove'){
                removeMovieFromCart($_GET['movie_id']);
                displayCart();
            }
        }
        else{displayCart();}
    }
    else
        {
            header("Location: ./logon.php");
            exit;
        }
}

function removeMovieFromCart($movieID)
{
    removeMovieFromShoppingCart($_SESSION["userId"], $movieID);
    displayCart();
}

?>