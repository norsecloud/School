// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE BELOW THIS LINE

function displayMovieInformation(movie_id)
{
	var request = new XMLHttpRequest();
	request.onreadystatechange = function() {
		document.getElementById("modalWindowContent").innerHTML = this.responseText;
		showModalWindow();
		};
	request.open("GET", "./movieinfo.php?movie_id=" + movie_id, true);
	request.send();
}

function forgotPassword()
{
	window.location.replace("./logon.php?action=forgot");
}

function showModalWindow()
{
    var modal = document.getElementById('modalWindow');
    var span = document.getElementsByClassName("_close")[0];

    span.onclick = function() 
    { 
        modal.style.display = "none";
    }

    window.onclick = function(event) 
    {
        if (event.target == modal) 
        {
            modal.style.display = "none";
        }
    }
 
    modal.style.display = "block";
}

// DO NOT REMOVE OR MODIFY THE CODE OR PLACE YOUR CODE ABOVE THIS LINE


// DO NOT REMOVE OR MODIFY THE SIGNATURE OF THE FUNCTIONS BELOW THIS LINE

function addMovie(imdbID)
{
    window.location.replace("./index.php?action=add&imdb_id=" + imdbID);
    return true;
}

function confirmCancel()
{
    let temp = window.confirm("click ok to return to shopping cart")
    if (temp) {
        window.location.replace("./index.php");
    }
    return temp;
}

function confirmCheckout()
{
    let temp = window.confirm("Do you wish to checkout")
    if (temp) {
        window.location.replace("./index.php?action=checkout");
    }
    return temp;
}

function confirmLogout()
{
    let temp = window.confirm("click ok to logout")
    if (temp) {
        window.location.replace("./logon.php?action=logoff");
    }
    return temp;
}

function confirmRemove(title, movieID)
{
    let temp = window.confirm("Click ok to remove " + title)
    if (temp) {
        window.location.replace("./index.php?action=remove&movie_id=" + movieID);
    }
    return temp;
}