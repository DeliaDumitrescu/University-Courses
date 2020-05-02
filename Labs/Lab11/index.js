// Import packages
const express = require("express");
const morgan = require("morgan");
const bodyParser = require("body-parser");
const cors = require("cors");
const { v1: uuidv1 } = require('uuid');

const fs = require("fs");

// Aplicatia
const app = express();

// Middleware
app.use(morgan("tiny"));
app.use(bodyParser.json());
app.use(cors());

// Create
app.post("/dogs", (req, res) => {        //Send data to server
  const dogsList = readJSONFile();
  var newId = uuidv1();
  var newDog =
  {
    name: req.body.name,
    img: req.body.img,
    id: newId
  };
  dogsList.push(newDog);
  writeJSONFile(dogsList);
  res.send(dogsList);
});

// Read One
app.get("/dogs/:id", (req, res) => {
  const dogsList = readJSONFile();
  var found = 0;
  for(var i = 0; i < dogsList.length; i++)
    if(dogsList[i].id == req.params.id)
    {
      res.send(dogsList[i]);
      found = 1;
      break;
    }
  if(found == 0)
      res.send("Not found!");
});

// Read All
app.get("/dogs", (req, res) => {
  const dogsList = readJSONFile();
  res.send(dogsList);
});

// Update
app.put("/dogs/:id", (req, res) => {
  const dogsList = readJSONFile();
  var found = 0;
  for(var i = 0; i < dogsList.length; i++)
        if(dogsList[i].id == req.params.id)
        {
            found = 1;
            dogsList[i].name = req.body.name;
            dogsList[i].img = req.body.img;
            res.send(dogsList[i]);
            break;
        }
    writeJSONFile(dogsList);
    if(found == 0)
      res.send("Not found");
});

// Delete
app.delete("/dogs/:id", (req, res) => {
  const dogsList = readJSONFile();
    var found = 0;
    for(var i = 0; i < dogsList.length; i++)
        if(dogsList[i].id == req.params.id)
        {
            dogsList.splice(i, 1);
            found = 1;
            break;
        }
    writeJSONFile(dogsList);
    if(found == 0) res.send("Not found!");
    else res.send("Item deleted!");

});

// Functia de citire din fisierul db.json
function readJSONFile() {
  return JSON.parse(fs.readFileSync("db.json"))["dogs"];
}
// Functia de scriere in fisierul db.json
function writeJSONFile(content) {
  fs.writeFileSync(
    "db.json",
    JSON.stringify({ dogs: content }),
    "utf8",
    err => {
      if (err) {
        console.log(err);
      }
    }
  );
}

app.listen("3000", () =>
  console.log("Server started at: http://localhost:3000")
);