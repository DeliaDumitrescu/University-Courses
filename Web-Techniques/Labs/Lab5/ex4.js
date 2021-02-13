function total(cart){

    const values = Object.values(cart);
    let sum = 0;

    for(let i of values){
        sum = sum + parseFloat(i);
    }
    return sum.toFixed(2);
}

var blackFridayCart = {
  telefon: "350",
  consola: "250",
  televizor: "450",
  iepurasPlus: "10.60",
  cercei: "20.34",
  geanta: "22.36"
}

console.log(total(blackFridayCart));