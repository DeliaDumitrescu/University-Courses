const Person = {
    nume: "Diana Popescu",
    varsta: 35,
    calitati: ["Inteligenta", "Descurcareata", "Iubitoare"]
}

console.log(Person.nume);
console.log(`Varsta: ${Person.varsta}`);
console.log('Calitati:\n' + Person.calitati.join('\n'))