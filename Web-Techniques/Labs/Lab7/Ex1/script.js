document.getElementById("story-button").addEventListener("click", function(){
    makestory();
});


function makestory(){
    var who = document.getElementById("person").value;
    var where = document.getElementById("places").value;
    var how = document.getElementById("adjective").value;
    var mystory = who + " a vizitat " + where + " si a fost foarte " + how + '.';

    var node = document.createElement('div');
    node.setAttribute("id", "story");
    var textnode = document.createTextNode(mystory);
    node.appendChild(textnode);
    document.body.appendChild(node);

}

