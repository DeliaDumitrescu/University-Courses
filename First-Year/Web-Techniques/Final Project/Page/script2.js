//PHOTO MANAGEMENT
const fileSelect = document.getElementById("fileSelect");
const fileElem = document.getElementById("fileElem");
const fileList = document.getElementById("fileList");

//TASK 1.14
fileSelect.addEventListener("click", function (e) {
  if (fileElem) {
    fileElem.click();
  }
  e.preventDefault();
}, false);

fileElem.addEventListener("change", uploadPhotos, false);
function uploadPhotos() {
  if (this.files.length)
  {
    const list = document.getElementById("photo-list");
    for (let i = 0; i < this.files.length; i++)
    {
      const li = document.createElement("li");
      li.classList.add("Photo");
      list.appendChild(li);

      const img = document.createElement("img");
      img.src = URL.createObjectURL(this.files[i]);
      img.height = 200;
      img.width = 200;

      img.onload = function() {
        URL.revokeObjectURL(this.src);
      }

      li.appendChild(img);
    }
  }
}

//NOTES MANAGEMENT

const notes = document.getElementById("notes");
document.getElementById("addNotes-button").addEventListener("click", addNotes);

//TASK 1.4
function addNotes(){
   var startExecution = performance.now();
   const notesInput = document.getElementById("notes-input").value;
   notes.innerHTML += notesInput;
   document.getElementById("notes-input").value = '';
   var endExecution = performance.now();
   console.log(endExecution - startExecution);
}
document.getElementById("updateNotes-button").addEventListener("click", updateNotes);
function updateNotes(){
    //var startExecution = performance.now();
    const notesInput = document.getElementById("notes-input");
    notesInput.value = document.getElementById("notes").innerHTML;
    notes.innerHTML = "";
   // var endExecution = performance.now();
     //console.log(endExecution - startExecution); console.log(endExecution - startExecution);


}

//MODAL MANAGEMENT
var personalInfoButton = document.getElementById("personal-info-button");
var closeButton = document.getElementById("close-button");
personalInfoButton.addEventListener("click", displayModal);
closeButton.addEventListener("click",closeModal);

function closeModal() {
  document.getElementById("Modal-Box").style.display = "none";
}
function displayModal(){
  document.getElementById("Modal-Box").style.display = "block";
}

//LOCAL STORAGE MANAGEMENT
var localStorage = window.localStorage;
document.getElementById("submit-button").addEventListener("click", function()
{
  var firstName = document.getElementById("first-name");
  var lastName = document.getElementById("last-name");
  var age = document.getElementById("age");
  var goal = document.getElementById("goal");

  localStorage.setItem("First Name", firstName.value);
  localStorage.setItem("Last Name", lastName.value);
  localStorage.setItem("Age", age.value);
  localStorage.setItem("Goal", goal.value);

  firstName.value = "";
  lastName.value = "";
  age.value = "";
  goal.value = "";

});
