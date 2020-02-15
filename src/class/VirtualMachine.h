/*
 * VirtualMachine.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_
	#include "../lib/Types.h"
	#include "../lib/Dupla.h"
	#include <vector>

	#define OPCODETAM 1<<16

	#define VM_FLAG_RUNNING 0
	#define VM_FLAG_DEBUG_LV 1


	class Contexto;
	class Thread;

	#define ASMJIT_STATIC
	#include "../asmjit/asmjit.h"

	using namespace asmjit;


	typedef uint64 (*Func)(Thread &t);


	class VirtualMachine{
		private:
			std::vector<Dupla<Contexto,uint16>> ct;
			std::vector<Dupla<Thread,uint16>> th;

			JitRuntime rt;

			//Contadores
			uint16 tamContex;
			uint16 tamThreads;

			void *VET[OPCODETAM];

			//Flags da VM
			uint16 vm_flags;

			//Instru��s iniciadas em JIT
			uint16 *func_pos;
			uint16 funcs;

			//Aloca��o dinamica
			void **recursos_alocados;
			uint32 qtd_res;

			void setStack();
			void setGerais();
			void setMov();
			void setArit();
			void setCmp();

			void finalize(uint16);
		public:

			VirtualMachine(uint8 = 0);
			~VirtualMachine();

			JitRuntime& getJitRuntime();

			//Return flags on finalize
			uint32 run();
			//Return flags on finalize
			uint32 runCommand();

			//Cria uma thread de execu��o passando como param o c�digo do ctx e a posi��o de entrada.
			void createThread(uint16,uint32);
			//Cria uma fun��o em JIT passando como param o c�digo do da instru��o e o c�digo de exec;
			void createFunction(uint16,CodeHolder&);
			//Carrega um contexto passando como param o bytecode e o tamanho
			uint16 loadContexto(uint8*,uint32);



			void* alloc_resorce(uint32);
			void free_resorce(void*);

			uint8 getDebugLevel();
			uint16 checkContexto(uint16);
			Contexto& getContexto(uint16);

	};


#endif /* VIRTUALMACHINE_H_ */
