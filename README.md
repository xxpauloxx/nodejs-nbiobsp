# NBioBSP Module for Nodejs

Digital fingerprint reader module for Python using Nitgen device.
Install the driver that is the "driver" directory.

PS: I used the versions 0.12.5 and 0.10.25.

```console
git clone https://github.com/paulopinda/nodejs-nbiobsp.git
cd nodejs-nbiobsp
./setup.sh
node test.js
```

#### Simple code

```javascript
var nbiobsp = require('./build/Release/nbiobsp');
var init = nbiobsp.init();

if(init == true){
	console.log("Insert the first fingerprint: ");
	var fir1 = nbiobsp.capture(4000);

	console.log("Insert the second fingerprint: ");
	var fir2 = nbiobsp.capture(4000);
}

console.log(nbiobsp.match(fir1, fir2));
nbiobsp.close()
```

#### Any problem? Report me, please.
### Paulo Roberto
paulo.pinda@gmail.com
