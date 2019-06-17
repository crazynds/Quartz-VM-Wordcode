/*
 * Contexto.cpp
 *
 * Created on: 10 de abr de 2019
 *   Author: lhlag
 */
#include "Thread.h"
#include <iostream>


Thread::Thread(){
	error_flags=0x00;
	cod_pointer=0;
	//vm=0;
	ct=0;
	cod=0;
	compare_flags=0;
	stack_pointer=0;
	stack=new uint64[256];
	stack_max=256;
	for(int x=0;x<256;x++)workspace[x]=0;
	vt=0;
}

Thread::~Thread(){
	delete[] stack;
}

void Thread::savePoint(){
	if(stack_pointer>=stack_max){
		incrementStack();
		if(error_flags&MAX_LIMIT_STACK_){
			return;
		}
	}
	stack[stack_pointer++]=((uint64)ct->getCodContext()<<32)+cod_pointer;
}

void Thread::saveInStack(uint64 p){
	if(stack_pointer>=stack_max){
		incrementStack();
		if(error_flags&MAX_LIMIT_STACK_){
			return;
		}
	}
	stack[stack_pointer++]=p;
}
uint64 Thread::recoverInStack(){
	if(stack_pointer!=0){
		if(stack_pointer<(stack_max/2)-64)decrementStack();
		return stack[--stack_pointer];
	}
	return 0;
}

void Thread::recoverPoint(){
	if(stack_pointer!=0){
		if(stack_pointer<(stack_max/2)-64)decrementStack();
		register uint64 p=stack[--stack_pointer];
		register uint16 k=uint16(p>>32);
		if(ct->getCodContext()!=k){
			if(vt->checkContexto(k)==0){
				error_flags|=INVALID_CHANGE_CONTEXT_;
				std::cout << "[ERROR] - Erro ao retornar para um contexto que n�o existe mais. (ID= " << k << ")" << std::endl;
				return;
			}
			Contexto &c=vt->getContexto(k);
			changeContexto(c);
		}
		cod_pointer=uint32(p);
		return;
	}
	error_flags|=MAX_LIMIT_STACK_;
}

void Thread::prepare(VirtualMachine &v,Contexto &ct,uint16 cntx,uint32 pos){
	this->ct=&ct;
	vt=&v;
	cod=ct.cod;
	mem.prepare(&ct,&error_flags);
	error_flags&=~((uint16)1);
	cod_pointer=pos;
}
void Thread::changeContexto(Contexto &c){
	mem.prepare(&c,&error_flags);
	cod=c.cod;
	cod_pointer=0;
	this->ct=&c;
}

VirtualMachine& Thread::getVirtualMachine(){
	return *vt;
}

uint16 Thread::runInstruction(void **funcs){
	uint16 opcode=getNext16();

	((Func)funcs[opcode])(*this);

	return opcode;
}

uint16 Thread::isFinalized(){
	return error_flags;
}
uint8* Thread::getPointerMemCode(){
	return ct->mem;
}

uint8 Thread::getNext8(){
	return cod[cod_pointer++];
}
uint16 Thread::getNextTwo8(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
uint16 Thread::getNext16(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
uint32 Thread::getNextTwo16(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
uint32 Thread::getNext32(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
uint64 Thread::getNextTwo32(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}
uint48 Thread::getNext48(){
	register uint48 x=*((uint48*)(&cod[cod_pointer]));
	cod_pointer+=6;
	return x;
}
uint64 Thread::getNext64(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}

uint8 Thread::checkUseCode(uint32 tam){
	if(cod_pointer+tam>ct->cod_len){
		error_flags|=OVERLOAD_COD_ERROR_;
	}
	return error_flags;
}

void Thread::setPontCode(uint32 t){
	cod_pointer=t;
}
uint32 Thread::getPontCode(){
	return cod_pointer;
}

Contexto& Thread::getContexto(){
	return *ct;
}


JitRuntime& Thread::getJitRuntime(){
	return vt->getJitRuntime();
}