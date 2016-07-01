console.log(" ");
var nbiobsp = require('./build/Release/nbiobsp');

var init = nbiobsp.init();

if(init == true){
	console.log("Posicione a primeira digital: ");
	var fir1 = nbiobsp.capture(4000);

	console.log("Posicione a segunda digital: ");
	var fir2 = nbiobsp.capture(4000);
}

console.log(nbiobsp.match(fir1, fir2));
nbiobsp.close()

