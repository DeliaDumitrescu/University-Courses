var tryy = 0;
var ind = 0;


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

function updateData(item, url, newNamee){
    return fetch(url + '/' + item, {
        method: 'PATCH',
        headers: {
        'Content-Type': 'application/json'},
         body: JSON.stringify({
            "name": newNamee,
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


//updateData(1, 'http://localhost:3000/dogs');
//deleteData(7, 'http://localhost:3000/dogs');
//deleteData(8, 'http://localhost:3000/dogs');



document.getElementById("create-button").addEventListener("click", function(){
    var name = document.getElementById("name").value;
    var img = document.getElementById("img").value;
    var to_insert = {
        "name": name,
        "img": img
    }
    insertData(to_insert, 'http://localhost:3000/dogs');
});

document.getElementById("delete-button").addEventListener("click", function(){
    var toDelete = document.getElementById("to-delete").value;
    deleteData(toDelete, 'http://localhost:3000/dogs' );
});

document.getElementById("edit-button").addEventListener("click", function(){
    var toEdit = document.getElementById("to-edit").value;
    var newName = document.getElementById("new-name").value;
    updateData(toEdit, 'http://localhost:3000/dogs', newName);
});
