const express = require("express");
const morgan = require("morgan");
const bodyParser = require("body-parser");
const cors = require("cors");
const { v1: uuidv1 } = require('uuid');

const fs = require("fs");
const app = express();
app.use(morgan("tiny"));
app.use(bodyParser.json());
app.use(express.static('Page'))
app.use(cors());

// Create
app.post("/tasks", (req, res) => {        //Send data to server
  const tasksList = readJSONFile();
  var newId = uuidv1();
  var newTask =
  {
    name: req.body.name,
    id: newId
  };
  tasksList.push(newTask);
  writeJSONFile(tasksList);
  res.send(tasksList);
});

// Read One
app.get("/tasks/:id", (req, res) => {
  const tasksList = readJSONFile();
  var found = 0;
  for(var i = 0; i < tasksList.length; i++)
    if(tasksList[i].id == req.params.id)
    {
      res.send(tasksList[i]);
      found = 1;
      break;
    }
  if(found == 0)
      res.send("Not found!");
});

// Read All
app.get("/tasks", (req, res) => {
  const tasksList = readJSONFile();
  res.send(tasksList);
});

// Update
app.put("/tasks/:id", (req, res) => {
  const tasksList = readJSONFile();
  var found = 0;
  for(var i = 0; i < tasksList.length; i++)
        if(tasksList[i].id == req.params.id)
        {
            found = 1;
            tasksList[i].name = req.body.name;
            res.send(tasksList[i]);
            break;
        }
    writeJSONFile(tasksList);
    if(found == 0)
      res.send("Not found");
});

// Delete
app.delete("/tasks/:id", (req, res) => {
  const tasksList = readJSONFile();
    var found = 0;
    for(var i = 0; i < tasksList.length; i++)
        if(tasksList[i].id == req.params.id)
        {
            tasksList.splice(i, 1);
            found = 1;
            break;
        }
    writeJSONFile(tasksList);
    if(found == 0) res.send("Not found!");
    else res.send("Item deleted!");

});

function readJSONFile() {
  return JSON.parse(fs.readFileSync("db.json"))["tasks"];
}

function writeJSONFile(content) {
  fs.writeFileSync(
    "db.json",
    JSON.stringify({ tasks: content }),
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