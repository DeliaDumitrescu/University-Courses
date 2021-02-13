const input = document.getElementById("task-input");
const editInput = document.getElementById("edit-input")
const addButton = document.getElementById("add-button");
const list = document.getElementById("taskList");
let updateButton = document.getElementById("update-button");

function getTasks() {
    fetch('http://localhost:3000/tasks')
        .then(function (response) {
            response.json().then(function (tasks) {
                appendTasksToDOM(tasks);
            });
        });
};

function postTask() {
    const task = {
        name: input.value
    }
    fetch('http://localhost:3000/tasks', {
        method: 'post',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(task)
    }).then(function () {
        getTasks();
        resetForm();
    });
}

function deleteTask(id) {
    fetch(`http://localhost:3000/tasks/${id}`, {
        method: 'DELETE',
    }).then(function () {
        getTasks();
    });
}

function editTask(task) {
    editInput.value = task.name;
    clearUpdateButtonEvents();
    updateButton.addEventListener('click', function () {
        updateTask(task.id)
    });

}

function updateTask(id) {
    const taskk = {
        name: editInput.value
    }
    fetch(`http://localhost:3000/tasks/${id}`, {
        method: 'PUT',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(taskk)
    }).then(function () {
        getTasks();
        clearUpdateButtonEvents();
        resetForm();
    });
}


function appendTasksToDOM(tasks) {
    while (list.firstChild) {
        list.removeChild(list.firstChild);
    }
    for (let i = 0; i < tasks.length; i++)
    {
        let name = document.createElement('span');
        name.innerText = tasks[i].name;

        let doneButton = document.createElement('button');
        doneButton.innerText = 'Done';
        doneButton.innerHTML = '<i class="fas fa-check-circle"></i>';
        doneButton.classList.add("done-button");
        doneButton.addEventListener('click', function () {
            name.style.setProperty("text-decoration", "line-through");
        });

        let editButton = document.createElement('button');
        editButton.innerText = 'Edit';
        editButton.innerHTML = '<i class="fas fa-cogs"></i>';
        editButton.classList.add("edit-button");
        editButton.addEventListener('click', function () {
            editTask(tasks[i])
        });

        let deleteButton = document.createElement('button');
        deleteButton.innerText = 'Delete';
        deleteButton.innerHTML = '<i class="fas fa-trash-alt"></i>';
        deleteButton.classList.add("delete-button");
        deleteButton.addEventListener('click', function () {
            deleteTask(tasks[i].id)
        });

        let li = document.createElement('li');
        li.appendChild(doneButton);
        li.appendChild(name);
        li.appendChild(editButton);
        li.appendChild(deleteButton);
        li.classList.add("list-item");
        list.appendChild(li);
    }
}

function resetForm() {
    input.value = '';
    editInput.value = '';
}

function clearUpdateButtonEvents() {
    let newUpdateButton = updateButton.cloneNode(true);
    updateButton.parentNode.replaceChild(newUpdateButton, updateButton);
    updateButton = document.getElementById("update-button");
}

addButton.addEventListener('click', postTask);
getTasks();

