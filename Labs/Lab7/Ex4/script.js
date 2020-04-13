var sessionExpired = setTimeout(function(){
    alert("Sesiune expirata");
}, 30000);


var Dog = {

    movePixels: 10,
    delayMs: 50,
    delayMsSpeed: 25;
    dogTimer: null,


    dogWalk: function(){
        var img = document.getElementsByTagName("img")[0];
        var currentLeft = parseInt(img.style.left);
        img.style.left = currentLeft + Dog.movePixels + "px";
        if (currentLeft > window.innerWidth - img.width) {
        img.style.left = "0px";}
   },


    speedDogWalk: function(){
        var img = document.getElementsByTagName("img")[0];
        var currentLeft = parseInt(img.style.left);
        img.style.left = currentLeft + Dog.movePixels + "px";
        if (currentLeft > window.innerWidth - img.width) {
        img.style.left = "0px";}
   },

    startDogWalk: function(){
       clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
       Dog.dogTimer = window.setInterval(this.dogWalk, Dog.delayMs);
       document.getElementById("info").innerText = "Viteza: "+ ((1000 * Dog.movePixels) / Dog.delayMs) + "px/secunda";
    },

    stopDogWalk: function(){
       clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30*1000);

        clearInterval(Dog.dogTimer);
    },

    startspeedDogWalk: function(){
      clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30*1000);
      Dog.stopDogWalk();
      dogTimer = window.setInterval(this.speedDogWalk, Dog.delayMsSpeed);
      document.getElementById("info").innerText = "Viteza: "+ ((1000 * Dog.movePixels) / Dog.delayMs) + "px/secunda";

    },

    resetSpeed: function(){
        clearTimeout(sessionExpired);
        sessionExpired = setTimeout(function(){
            alert("Sesiune expirata");
        }, 30000);
      var img = document.getElementsByTagName("img")[0];
      var currentLeft = parseInt(img.style.left);
      img.style.left = currentLeft + Dog.movePixels + "px";
      img.style.left = "0px";
    }

};

  var btn = document.createElement("button");
  btn.appendChild(document.createTextNode("Reset"));
  btn.id = "reset-button";
  document.body.append(btn);

   document.getElementById("start-button").addEventListener("click", function(){
      Dog.startDogWalk();
      document.getElementById("start-button").disabled = true;
  });

  document.getElementById("stop-button").addEventListener("click", function(){
      Dog.stopDogWalk();
      document.getElementById("start-button").disabled = false;
  });

  document.getElementById("speed-button").addEventListener("click", function(){
      Dog.startspeedDogWalk();
  });

   document.getElementById("reset-button").addEventListener("click", function(){
      Dog.resetSpeed();
  });
