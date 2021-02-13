// TASK 2.8
let answerButton = document.getElementById("answer-button")
var answered = 0, timeIsUp = 0;

function startAnswerTimer(){
    setTimeout(answer, 3000);
}

answerButton.addEventListener("click", function(){
    answered = 1;
    if(timeIsUp == 1)
        {
            document.getElementById("question").style.display = "none";
            document.getElementById("answer").innerHTML = "Sorry, you are wrong!";
        }

})

function answer(){
        if(answered == 0)
        {
            alert("Time is up!");
            document.getElementById("question-answer").disabled = true;
        }
        else
        {
            document.getElementById("answer").innerHTML = "Congratulations!";
            answerButton.disabled = true;
        }
        timeIsUp = 1;
}


// TASK 2.4
var Timer, timeSpent;

function getLocalStoredTime(){
    if(localStorage.getItem('timeSpent') == null)
        return 0;
    timeSpent = +localStorage.getItem('timeSpent');
    return timeSpent;
}

function StartTimer(){
    Timer = setInterval(getTimeSpent, 1000);
}

function getTimeSpent(){
    localStorage.setItem('timeSpent', getLocalStoredTime() + 1000);

    var seconds =  Math.round(timeSpent / 1000 % 60);
    var minutes = Math.round(timeSpent / 1000 / 60) % 60;
    var hours = Math.round(timeSpent / 1000 / 60 / 60);

    document.getElementById("time").innerHTML = "Time spent on your personal agenda is: " + hours + " hours " + minutes + " minutes " + seconds + " seconds. Keep up the great work!";
}

window.onload = StartTimer();

//TASK 3.13
var timeoutID, currentSeconds = 0, timer;
var timerText = document.getElementById("timer-text");
var seconds = document.getElementById("seconds");

function startTimer() {
    closeModal();
    timeoutID = window.setTimeout(goInactive, 5000);
}

function resetTimer(e) {
    window.clearTimeout(timeoutID);
    clearInterval(timer);
    timerText.style.display = 'none';
    currentSeconds = 4;
    goActive();
}

function goInactive() {
    clearInterval(timer);
    displayModal();
    currentSeconds = 4;
    timer = setInterval(function(){
        currentSeconds++;
        seconds.textContent = currentSeconds;
        timerText.style.display = 'block';
    }, 1000)
}

function goActive() {
    startTimer();
}

function closeModal() {
  document.getElementById("Modal-Box-IDLE").style.display = "none";
}
function displayModal(){
  document.getElementById("Modal-Box-IDLE").style.display = "block";
}

this.addEventListener("click", resetTimer, false);
this.addEventListener("dblclick", resetTimer, false);
//this.addEventListener("mouseover", resetTimer, false);
//this.addEventListener("mouseout", resetTimer, false);
this.addEventListener("mousedown", resetTimer, false);
this.addEventListener("mouseup", resetTimer, false);
this.addEventListener("mouseleave", resetTimer, false);
this.addEventListener("keydown", resetTimer, false);
this.addEventListener("keyup", resetTimer, false);
this.addEventListener("keypress", resetTimer, false);
this.addEventListener("mousemove", resetTimer, false);
this.addEventListener("scroll", resetTimer, false);
this.addEventListener("touchmove", resetTimer, false);

startTimer();

// TASK 2.1
var birthdayButton = document.getElementById("birthday-button")

function getAge(dateString) {
  var now = new Date();
  var today = new Date(now.getYear(), now.getMonth(), now.getDate());

  var currentYear = now.getFullYear();
  var currentMonth = now.getMonth() + 1;
  var currentDay = now.getDate();
  var currentHour = now.getHours();
  var currentMinute = now.getMinutes();
  var currentSecond = now.getSeconds();

  var birthDate = new Date(dateString.substring(0, 4),
                     dateString.substring(5, 7) - 1,
                     dateString.substring(8, 10)
                     );

  var birthYear = birthDate.getFullYear();
  var birthMonth = birthDate.getMonth() + 1;
  var birthDay = birthDate.getDate();

  var ageYear = currentYear - birthYear;

  if(currentMonth >= birthMonth)
    var ageMonth = currentMonth - birthMonth;
  else
{
    ageYear--;
    var ageMonth = 12 + currentMonth - birthMonth;
 }

 if(currentDay >= birthDay)
    var ageDay = currentDay - birthDay;
else
{
    ageMonth--;
    var ageDay = 31 + currentDay - birthDay;

    if(ageMonth < 0)
    {
        ageMonth = 11;
        ageYear--;
    }

}

document.getElementById("Age").innerHTML = "Your age: " + ageYear + " years " + ageMonth + " months " + ageDay + " days " + currentHour + " hours " + currentMinute + " minutes " + currentSecond + " seconds old" ;
}

birthdayButton.addEventListener("click", function() {
    var birthday = document.getElementById("birthday").value;
     setInterval(function(){getAge(birthday);}, 1000);
})

// TASK 3.12
var events = ''

function addEventTime(){
    var now = new Date();
    var currentYear = now.getFullYear();
    var currentMonth = now.getMonth() + 1;
    if(currentMonth < 10)
        currentMonth = '0' + currentMonth;
    var currentDay = now.getDate();
     if(currentDay< 10)
        currentDay = '0' + currentDay;
    var currentHour = now.getHours();
     if(currentHour < 10)
        currentHour = '0' + currentHour;
    var currentMinute = now.getMinutes();
     if(currentMinute < 10)
        currentMinute = '0' + currentMinute;
    var currentSecond = now.getSeconds();
     if(currentSecond < 10)
        currentSecond = '0' + currentSecond;
    events += currentYear + '/' + currentMonth + '/' + currentDay + ' ' + currentHour + ':' + currentMinute + ':' + currentSecond;
}

window.addEventListener("click", function(){
    var x = event.clientX;
    var y = event.clientY;
    addEventTime();
    events +=' click: coords ' + x + ' ' + y + '<br>';
})

window.addEventListener("keydown", function(){
    addEventTime();
    events +=' key-down, key: ' +  event.key + '<br>';
})

window.addEventListener("keyup", function(){
    addEventTime();
    events +=' key-up, key: ' +  event.key + '<br>';
})


document.getElementById("event-button").addEventListener("click", function(){document.getElementById("events").innerHTML = events;});

function mouseDown() {
  document.getElementById("myP").style.color = "#EE82EE";
    var x = event.clientX;
    var y = event.clientY;
    addEventTime();
    events +=' mouse-down: coords ' + x + ' ' + y + '<br>';

}

function mouseUp() {
  document.getElementById("myP").style.color = "#87CEEB";
    var x = event.clientX;
    var y = event.clientY;
    var now = new Date();
    var currentYear = now.getFullYear();
    var currentMonth = now.getMonth() + 1;
    if(currentMonth < 10)
        currentMonth = '0' + currentMonth;
    var currentDay = now.getDate();
     if(currentDay< 10)
        currentDay = '0' + currentDay;
    var currentHour = now.getHours();
     if(currentHour < 10)
        currentHour = '0' + currentHour;
    var currentMinute = now.getMinutes();
     if(currentMinute < 10)
        currentMinute = '0' + currentMinute;
    var currentSecond = now.getSeconds();
     if(currentSecond < 10)
        currentSecond = '0' + currentSecond;
    events += currentYear + '/' + currentMonth + '/' + currentDay + ' ' + currentHour + ':' + currentMinute + ':' + currentSecond;
    events +=' mouse-up: coords ' + x + ' ' + y + '<br>';
}


function doubleClick() {
    var x = event.clientX;
    var y = event.clientY;
    addEventTime();
    events +=' doubleclick: coords ' + x + ' ' + y + '<br>';

}

document.getElementById("events").style.color = "pink";