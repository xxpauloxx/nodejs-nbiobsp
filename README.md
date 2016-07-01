# Módulo NBioBSP Nodejs

Módulo para utilização do leitor biométrico Nitgen Hamster III em Nodejs 0.12.5 e 0.10.25, em breve faremos uma atualização para Nodejs 5.5.0. Faça a instalação do driver que está no diretório driver(64 bits, mas existe 32 bits na Internet também).

```console
git clone https://github.com/izepa/nodejs-nbiobsp-module.git
cd nodejs-nbiobsp-module
./setup.sh
node test.js
```

#### Código para testar o módulo.

```javascript
var nbiobsp = require('./build/Release/nbiobsp');

var init = nbiobsp.init();

if(init == true){
	console.log("Posicione a primeira digital: ");
	var fir1 = nbiobsp.capture(4000);

	console.log("Posicione a segunda digital: ");
	var fir2 = nbiobsp.capture(4000);
}

nbiobsp.close()
```

