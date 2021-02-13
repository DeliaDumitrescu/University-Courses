function f(obj){
    console.log(`"${obj.titlu}" a durat ${obj.durata} minute. Actori: ${obj.actori.join(', ')}` );
}

const IMDB = {
    titlu: "The Shawshank Redemption",
    durata: 142,
    actori: ["Tim Robbins", "Morgan Freeman", "Bob Gunton", "William Sadler"]
}

f(IMDB)