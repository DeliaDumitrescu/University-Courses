function multiplicator(element) {
    return 2 * element;
}

Array.prototype.myMap = function(callbackFunction) {

  let newArray = [];

  for(let i = 0; i < this.length; i++){
    newArray.push(callbackFunction(this[i]));
   }

  return newArray;
}


console.log([1,2,3].map(multiplicator)); // [2,4,6]

console.log([1,2,3].myMap(multiplicator)); // [2,4,6]