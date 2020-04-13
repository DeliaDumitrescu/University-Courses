/*var myrequest = new XMLHttpRequest();
myrequest.open('GET','http://localhost:3000/dogs');

myrequest.onload = function(){
    var mydata = JSON.parse(myrequest.responseText);
    console.log(mydata[0]);
};

myrequest.send();
*/
var tryy = 0;

fetch('http://localhost:3000/dogs')
  .then((response) => {      //respone->promise type
    return response.json();  // ->promise type
  })
  .then((data) => {
    for(var i of data)
    {
        var name = i.name;
        var imgurl = i.img;

        if(tryy == 0)
        {   ul = document.createElement("ul");
            tryy = 1;}

        var listElement = document.createElement("li");
        ul.appendChild(listElement);
        listElement.appendChild(document.createTextNode(name));
        listElement.appendChild(document.createElement("div"));
        var img = document.createElement("img");
        img.src = imgurl;
        listElement.appendChild(img);
        document.body.appendChild(ul);

    }
  });