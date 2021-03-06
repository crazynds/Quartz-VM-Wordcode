
#include "../../../class/Thread.h"



void call_ctx_c(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint16 ctx=uint16(t.workspace[t.getNext8()]);
	uint32 pon=t.getNext32();
	t.savePoint();
#ifndef _FAST_MODE
	if(t.getVirtualMachine().checkContext(ctx)==0){
		t.setErrorFlags(INVALID_CHANGE_CONTEXT_);
		std::cout << "[ERROR] - Erro ao entrar em um Context inexistente. (ID= " << ctx << ")" << std::endl;
		return;
	}
#endif
	Context &ct=t.getVirtualMachine().getContext(ctx);
	t.changeContext(&ct);
	t.setPontCode(pon);
	t.checkUseCode(2);
}

void call_ctx_w(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
	uint16 ctx=uint16(t.workspace[t.getNext8()]);
	uint32 pon=uint32(t.workspace[t.getNext8()]);
	t.savePoint();
#ifndef _FAST_MODE
	if(t.getVirtualMachine().checkContext(ctx)==0){
		t.setErrorFlags(INVALID_CHANGE_CONTEXT_);
		std::cout << "[ERROR] - Erro ao entrar em um Context inexistente. (ID= " << ctx << ")" << std::endl;
		return;
	}
#endif
	Context &ct=t.getVirtualMachine().getContext(ctx);
	t.changeContext(&ct);
	t.setPontCode(pon);
	t.checkUseCode(2);
}

void call_c(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 p=t.getNext32();
	t.savePoint();
	t.setPontCode(p);
	t.checkUseCode(2);
}

void call_m(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(6);
#endif
	uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	t.savePoint();
	t.setPontCode(p);
	t.checkUseCode(2);
}
void call_w(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(1);
#endif
	uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	t.savePoint();
	t.setPontCode(p);
	t.checkUseCode(2);
}

void ret(Thread &t){
	t.recoverPoint();
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}




void push_w(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(3);
#endif
	t.saveInStack(t.workspace[t.getNext8()]);
}
void push_c(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	t.saveInStack(t.getNext64());
}


void pop_w(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(3);
#endif
	t.workspace[t.getNext8()]=t.recoverInStack();
}
