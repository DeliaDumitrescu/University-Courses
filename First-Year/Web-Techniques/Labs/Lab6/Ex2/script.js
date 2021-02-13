document.body.style.fontFamily = "Arial, sans-serif";

document.getElementById("nickname").innerHTML = "Delia";
document.getElementById("favorites").innerHTML = "Pets, Movies, Sleep!";
document.getElementById("hometown").innerHTML = "Bucharest";

var listElements = document.getElementsByTagName("li");
for(var i = 0; i < listElements.length; i++){
    listElements[i].classList.add("list-item");
}

var myImage = document.createElement("IMG");
myImage.setAttribute("id", "mePhoto");
myImage.src = "305a2eff-2204-48f7-a375-9a0aa3bb3662.jpg";
document.body.appendChild(myImage);
document.getElementById("mePhoto").width = "300";