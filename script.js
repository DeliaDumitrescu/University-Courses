function square(){
    var nr = document.getElementById("square-input").value;
    return nr * nr;
}

function half(){
    var nr = document.getElementById("half-input").value;
    return nr / 2;
}

function percent(){
    var per = document.getElementById("percent1-input").value;
    var nr2 = document.getElementById("percent2-input").value;
    return (per / 100) * nr2;
}

function area(){
    var r = document.getElementById("area-input").value;
    console.log(r);
    return 3,14 * r * r;
}

function show(to_show){

    var node = document.createElement('div');
    node.setAttribute("id", "solution");
    var textnode = document.createTextNode(to_show);
    node.appendChild(textnode);
    document.body.appendChild(node);

}

document.getElementById("square-button").addEventListener("click", function(){
    var to_show = square();
    show(" Patrat: " + to_show);
});

document.getElementById("half-button").addEventListener("click", function(){
    var to_show = half();
    show(" Jumatate: " + to_show);
});

document.getElementById("percent-button").addEventListener("click", function(){
    var to_show = percent();
    show(" Procent: " + to_show)
});

//document.getElementById("area-button").addEventListener("click", function(){
  //  to_show = area();
    //show(" Arie: " + to_show);
//});

document.getElementById("area-input").addEventListener("keypress", area2);

function area2(e){
    var to_show = e.keyCode;
    show(" Arie: " + to_show);

}



