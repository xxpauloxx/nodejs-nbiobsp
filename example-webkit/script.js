
function clickCapture(){
	var nbiobsp = require('../build/Release/nbiobsp');
	var init = nbiobsp.init();
	var fir;

	fir = nbiobsp.capture(4000);
	spn = document.getElementById('fir');
	spn.text = fir;
	console.log(fir);
	nbiobsp.close();
}

window.onload = function(){
	setTimeout(function(){
		clickCapture();
	},3000);
}

