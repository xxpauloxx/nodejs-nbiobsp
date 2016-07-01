# include <node.h>
# include <iostream>
# include <cstring>
# include <string>
# include "nbiobsp.h"


using namespace std; 

namespace NBioBSP {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;		
	using v8::Number;
	using v8::Boolean;
	using v8::Value;
	
	// Inicialização do equipamento.
	void InitModule(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = args.GetIsolate();

	    if ( NBioAPI_Init(&bspHandle) != NBioAPIERROR_NONE ){
	        args.GetReturnValue().Set(Boolean::New(isolate, false));
	    }

	    idDevice = NBioAPI_DEVICE_ID_AUTO; // Abrindo o dispositivo para uso.
	    ret = NBioAPI_OpenDevice(bspHandle, idDevice);
	    if ( ret != NBioAPIERROR_NONE ){
	        args.GetReturnValue().Set(Boolean::New(isolate, false));
	    }

	  args.GetReturnValue().Set(Boolean::New(isolate, true));
	}

	// Captura do template FIR da digital.
	void Capture(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		double timeout = 5;

	  	if(args.Length() == 1){
  			v8::String::Utf8Value nameFromArgs(args[0]->ToString());
  			std::string name = std::string(*nameFromArgs);
  			timeout = ::atof(name.c_str());
	  	}

    	NBioAPI_FIR_HANDLE firHandle;
    	NBioAPI_FIR_PURPOSE purpose;

	    purpose = NBioAPI_FIR_PURPOSE_ENROLL;
	    ret = NBioAPI_Capture(
	        bspHandle,   // Módulo para manusear módulo NBioBSP
	        purpose,     // Propósito da captura
	        &firHandle,  // Manipular o FIR capturado
	        timeout,     // Timeout para captura
	        NULL,        // Dados para auditoria
	        NULL         // Opção da janela
	    );

		// Capturar FIR da digital e retornar o hash do template.
		NBioAPI_FIR_TEXTENCODE textFIR;
		ret = NBioAPI_GetTextFIRFromHandle(bspHandle, firHandle, &textFIR, NBioAPI_FALSE);

	    if(ret == 0){ args.GetReturnValue().Set(String::NewFromUtf8(isolate, textFIR.TextFIR));}
	    else{ args.GetReturnValue().Set(String::NewFromUtf8(isolate, "NULL")); }
	}

	// Método para fazer match de digitais.
	// nbiobsp.match(FIR_DB, FIR_CAPTURED)
  	void Match(const FunctionCallbackInfo<Value>& args) {
	    Isolate* isolate = args.GetIsolate();

  		if(args.Length() == 2){
  			NBioAPI_BOOL result;
    		NBioAPI_INPUT_FIR inputFirCaptured, inputFirStored;

	  		v8::String::Utf8Value storedFromArgs(args[0]->ToString());
	  		std::string firStored = std::string(*storedFromArgs);

	  		v8::String::Utf8Value capturedFromArgs(args[1]->ToString());
	  		std::string firCaptured = std::string(*capturedFromArgs);

	  		// Convertendo para string as FIRs do argumento do método.
    		std::string valueFirCaptured(firCaptured);
    		std::string valueFirStored(firStored);

			// Extraindo os tamanhos dos valores do template capturado e armazenado.
		    int lenFirCaptured = strlen(valueFirCaptured.c_str());
		    int lenFirStored = strlen(valueFirStored.c_str());

		    // Extraindo o hash do template FIR capturado.
		    NBioAPI_FIR_TEXTENCODE textFirCaptured; 
		    textFirCaptured.IsWideChar = NBioAPI_FALSE;         
		    textFirCaptured.TextFIR = new NBioAPI_CHAR[lenFirCaptured+1];
		    memcpy(textFirCaptured.TextFIR, valueFirCaptured.c_str(), lenFirCaptured+1);
		 
		    // Registrando o hash do template FIR no Input de FIR capturado.
		    inputFirCaptured.Form = NBioAPI_FIR_FORM_TEXTENCODE; 
		    inputFirCaptured.InputFIR.TextFIR = &textFirCaptured;

		    // Extraindo o hash do template FIR armazenado.
		    NBioAPI_FIR_TEXTENCODE textFirStored; 
		    textFirStored.IsWideChar = NBioAPI_FALSE;  
		    textFirStored.TextFIR = new NBioAPI_CHAR[lenFirStored+1];       
		    memcpy(textFirStored.TextFIR, valueFirStored.c_str(), lenFirStored+1); 

		    // Registrando o hash do template FIR no Input de FIR armazenado.
		    inputFirStored.Form = NBioAPI_FIR_FORM_TEXTENCODE; 
		    inputFirStored.InputFIR.TextFIR = &textFirStored;

		    // Fazer match das FIR e armazenar o resultado em result.
		    ret = NBioAPI_VerifyMatch( 
		        bspHandle,      	// Manipulador do módulo NBioBSP
		        &inputFirCaptured, 	// Primeira FIR
		        &inputFirStored,  	// Segunda FIR
		        &result,    		// Resultado da comparação
		        NULL    			// Payload
		    );     
	    
		    if(result == NBioAPI_TRUE){ 
		    	args.GetReturnValue().Set(Boolean::New(isolate, true));
		    }
		    else {
		    	args.GetReturnValue().Set(Boolean::New(isolate, false));
		    }
  		}
		else {
			args.GetReturnValue().Set(Boolean::New(isolate, false));
		}	    
  	}

  	void About(const FunctionCallbackInfo<Value>& args) {
  		std::cout << "Powered by Izepa.me :)" << std::endl;
		std::cout << "http://izepa.me - contato@izepa.me" << std::endl;
  	}

  	void Close(const FunctionCallbackInfo<Value>& args){
  		ret = NBioAPI_CloseDevice(bspHandle, idDevice);
		ret = NBioAPI_Terminate(bspHandle);
  	}

	void init(Local<Object> exports) {
	  NODE_SET_METHOD(exports, "about", About);
	  NODE_SET_METHOD(exports, "init", InitModule);
	  NODE_SET_METHOD(exports, "capture", Capture);
	  NODE_SET_METHOD(exports, "match", Match);
	  NODE_SET_METHOD(exports, "close", Close);
	}

	NODE_MODULE(nbiobsp, init)

}  