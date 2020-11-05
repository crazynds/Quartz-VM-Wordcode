//============================================================================
// Name        : ByteCodeIV.cpp
// Author      : Luiz Henrique Broch Lago
// Version     : 0.02.020
// Copyright   : Nextline
// Description :
//============================================================================

#include "lib/Types.h"
#include "class/Contexto.h"
#include "class/CodeLoader.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "class/VirtualMachine/VirtualMachine.h"

#define DEBUG 3

using namespace std;


int main(int argc, char **argv) {
	VirtualMachine *vm;
	uint8 debug=3;
	FileLoader *c;
	cout << "$$$$$ INICIANDO $$$$$" << endl;
	{
		if(argc>1)c=new FileLoader(argv[1],DEBUG);
		else c=new FileLoader((char*)"../codes/code.bt",DEBUG);
		if(c->getTam()==0){
			cout << "[ERROR] - N�o foi possivel carregar o c�digo, m�quina virtual desligando!";
			getchar();
			return 0;
		}
	}
	{
		if(argc>2)for(int x=0;argv[2][x]!='\0';x++){
			if(argv[2][x]=='g' || argv[2][x]=='G'){
				debug=1;
			}
		}
	}
	{
		vm=new VirtualMachine(DEBUG);
		uint16 context=vm->loadContexto(c->getCode(),c->getTam());
		vm->createThread(context,0);
	}
	delete c;
	{
		clock_t max=clock();
		uint64 flag=0;
		if(debug){
			while(!flag){
				flag=vm->runCommand();
			}
		}else flag=vm->run();
		cout<<"[INFO] - Dura��o total: "<< ( clock() - max )/(double)CLOCKS_PER_SEC << endl;
	}


	delete vm;
	return 0;
}
