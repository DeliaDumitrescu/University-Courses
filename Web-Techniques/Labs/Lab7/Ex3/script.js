var sessionExpired = setTimeout(function(){
    alert("Sesiune expirata!");
}, 30000);

var movePixels = 10;
var delayMs = 50;
var delayMsSpeed = 25;
var dogTimer = null;

  function dogWalk() {
    var img = document.getElementsByTagName("img")[0];
    var currentLeft = parseInt(img.style.left);
    img.style.left = currentLeft + movePixels + "px";
    if (currentLeft > window.innerWidth - img.width) {
      img.style.left = "0px";

    }
  }

   function speedDogWalk() {
    var img = document.getElementsByTagName("img")[0];
    var currentLeft = parseInt(img.style.left);
    img.style.left = currentLeft + movePixels + "px";
    if (currentLeft > window.innerWidth - img.width) {
      img.style.left = "0px";
    }
  }


  function startDogWalk() {
    clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
    dogTimer = window.setInterval(dogWalk, delayMs);
    document.getElementById("info").innerText = "Viteza: "+ ((1000 * movePixels) / delayMs) + "px/secunda";
  }

  function stopDogWalk() {
    clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
    clearInterval(dogTimer);
  }

  function startspeedDogWalk(){
    clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
    stopDogWalk();
    dogTimer = window.setInterval(speedDogWalk, delayMsSpeed);
    document.getElementById("info").innerText = "Viteza: "+ ((1000 * movePixels) / delayMs) + "px/secunda";
  }

  function resetSpeed(){
    clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
    var img = document.getElementsByTagName("img")[0];
    var currentLeft = parseInt(img.style.left);
    img.style.left = currentLeft + movePixels + "px";
    img.style.left = "0px";
  }


  document.getElementById("start-button").addEventListener("click", function(){
      startDogWalk();
      document.getElementById("start-button").disabled = true;
  })
  document.getElementById("stop-button").addEventListener("click", function(){
      stopDogWalk();
      document.getElementById("start-button").disabled = false;
  })
  document.getElementById("speed-button").addEventListener("click", function(){
      startspeedDogWalk();
  })

  var btn = document.createElement("button");
  btn.appendChild(document.createTextNode("Reset"));
  btn.id = "reset-button";
  document.body.append(btn);

   document.getElementById("reset-button").addEventListener("click", function(){
      resetSpeed();
  })

