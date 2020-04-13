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
    })
    .catch((error) => {
        console.log("Ey!");
    });



 function deleteData(item, url) {
  return fetch(url + '/' + item, {
    method: 'delete'
  })
  .then(response => response.json());
}

function updateData(item, url){
    return fetch(url + '/' + item, {
        method: 'PATCH',
        headers: {
        'Content-Type': 'application/json'},
         body: JSON.stringify({
            "name": "I changed my name! I'm PUFFY now!",
            "img": item.img
        })
    })
    .then(response => response.json());

}

function insertData(element, url){
    return fetch(url, {
        method: 'POST', // or 'PUT'
        headers: {
        'Content-Type': 'application/json'},
        body: JSON.stringify(element),
        })
    .then((response) => response.json())
    .then((data) => {
        console.log('Success:', data);
    })
    .catch((error) => {
        console.error('Error:', error);
    });
}

const dataa = {
    "name": "BOBBY",
    "img": "https://images.theconversation.com/files/319375/original/file-20200309-118956-1cqvm6j.jpg?ixlib=rb-1.1.0&q=45&auto=format&w=1200&h=1200.0&fit=crop"
 };

///insertData(dataa, 'http://localhost:3000/dogs')

updateData(1, 'http://localhost:3000/dogs');
deleteData(2, 'http://localhost:3000/dogs');


document.getElementById("button").addEventListener("click", function(){
    var name = document.getElementById("name").value;
    var img = document.getElementById("img").value;
    var to_insert = {
        "name": name,
        "img": img
    }
    insertData(to_insert, 'http://localhost:3000/dogs');
});