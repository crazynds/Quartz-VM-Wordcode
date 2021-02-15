/*
 * VirtualMachine.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_
	#include "../../lib/Types.h"
	#include "../../lib/Dupla.h"
	#include <vector>
	#include "ManagerOpcodes.h"
	#include "ManagerResources.h"

	#define OPCODETAM 1<<16

	//ocup 1 bit
	#define VM_FLAG_RUNNING 0
	//ocup 2 bits
	#define VM_FLAG_DEBUG_LV 1
	//ocup 1 bit
	#define VM_FLAG_EXCEPTION 3
    /*
     * Exce��es devem ser lan�adas sempre que algo fora da execu��o planejado do usuario ocorrer
     * Exemplos:
     *  - Carregar um c�digo n�o v�lido para a VM
     *  - Carregar c�digos com execu��es invalidas
     *  - VM muito antiga para rodar determinado c�digo
     *  - Falha interna da VM
     */


	class Context;
	class Thread;


	typedef uint64 (*Func)(Thread &t);


	class VirtualMachine{
		private:

			//Contexts e Threads
			uint16 tamContex;
			uint16 tamThreads;
			std::vector<Dupla<Context,uint16>> ct;
			std::vector<Dupla<Thread,uint16>> th;


			//Flags da VM
			uint16 vm_flags;


			void *VET[OPCODETAM];
			ManagerOpcodes manJit;
			//ManagerResources manRes;


			//Aloca��o dinamica
			void **recursos_alocados;
			uint32 qtd_res;


			uint32 runAllThread1Time(uint32);
			void finalize();
		public:

			VirtualMachine(uint8 = 0);
			~VirtualMachine();


			//Return flags on finalize
			uint32 run();
			//Return flags on finalize
			uint32 runCommand();


			//Cria uma thread de execu��o passando como param o c�digo do ctx e a posi��o de entrada.
			void createThread(uint16,uint32);
			//Carrega um Context passando como param o bytecode e o tamanho
			uint16 loadContext(uint8*,uint32);



			void* alloc_resorce(uint32);
			void free_resorce(void*);
			void* realloc_resorce(void*,uint32);

			uint16 checkContext(uint16);
			uint8 getDebugLevel();
			Context& getContext(uint16);
			bool isRunning();
			bool isExceptionCatched();

			ManagerOpcodes& getManagerOpcodes();
	};


#endif /* VIRTUALMACHINE_H_ */
