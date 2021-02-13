favoriteMovies = [

    {
        titlu: "Fight Club",
        durata: 151,
        actori: ["Edward Norton", "Brad Pitt", "Meat Loaf"],
        vizionat: 1,
        imgUrl: "https://m.media-amazon.com/images/M/MV5BMmEzNTkxYjQtZTc0MC00YTVjLTg5ZTEtZWMwOWVlYzY0NWIwXkEyXkFqcGdeQXVyNzkwMjQ5NzM@._V1_.jpg"
    },

    {
        titlu: "The Shawshank Redemption",
        durata: 142,
        actori: ["Tim Robbins", "Morgan Freeman", "Bob Gunton", "William Sadler"],
        vizionat: 1,
        imgUrl: "https://upload.wikimedia.org/wikipedia/ro/c/cb/The_Shawshank_Redemption.jpg"
    },

    {
        titlu: "V for Vendetta",
        durata: 143,
        actori: ["Natalie Portman", "Hugo Weaving", "Stephen Rea"],
        vizionat:0,
        imgUrl: "https://irs.www.warnerbros.com/keyart-jpeg/movies/media/browser/v_for_vendetta_key_art.jpg"
    }

];

for(var i = 0; i < favoriteMovies.length; i ++){

    var newP = document.createElement("p");
    var node = document.createTextNode(favoriteMovies[i].titlu);
    newP.appendChild(node);
    document.body.appendChild(newP);

}


for(var i = 0; i < favoriteMovies.length; i ++){

    var newP = document.createElement("p");
    newP.setAttribute("id",i);
    var node = document.createTextNode(favoriteMovies[i].titlu);
    newP.appendChild(node);
    document.body.appendChild(newP);

    if(favoriteMovies[i].vizionat == 1){
        document.getElementById(i).style.color = "green";
    }

    else{
        document.getElementById(i).style.color = "red";
    }


    ul = document.createElement("ul");

    var li = document.createElement("li");
    li.innerHTML = favoriteMovies[i].durata;
    ul.appendChild(li);

    var li = document.createElement("li");
    li.innerHTML = favoriteMovies[i].actori;
    ul.appendChild(li);

    var li = document.createElement("li");
    li.innerHTML = favoriteMovies[i].vizionat;
    ul.appendChild(li);

    var myImage = document.createElement("IMG");
    myImage.setAttribute("id", "mePhoto");
    myImage.src = favoriteMovies[i].imgUrl;
    document.body.appendChild(myImage);
    document.getElementById("mePhoto").width = "300";


    document.body.appendChild(ul);

}
