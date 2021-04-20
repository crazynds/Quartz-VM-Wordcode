/*
 * ExceptionsStrings.h
 *
 *  Created on: 19 de ago de 2020
 *      Author: lhlag
 */

#ifndef LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_
#define LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_

	#include <string>

	static const std::string _INTERNAL_ERRO_INVALID_FUNCIONALITY = "Erro interno da m�quina virtua. Funcionalidade inv�lida!";

	static const std::string _OVERLOAD_CODE = "Fim do c�digo encontrado em local invalido!";

	static const std::string _LOAD_CONTEXT_NOT_VALID_STR = "Erro ao tentar criar um Context inv�lido!";

	static const std::string _CREATE_FUNCTION_JIT_STR = "Erro ao criar fun��o jit!";
	static const std::string _ERROR_JIT_CREATE_NOT_FOUND_REGISTER_TYPE = "Erro ao criar um jit em tempo de execu��o, tipo ou tamanho de registrador n�o encontrado!";
	static const std::string _ERROR_JIT_CREATE_ANY_REGISTER_FREE = "Erro ao criar um jit em tempo de execu��o, nenhum registrador livre para uso encontravel!";
	static const std::string _ERROR_JIT_CREATE_ANY_COMAND_FOUND = "Erro ao criar um jit em tempo de execu��o, nenhum comando equivalente encontrado depois da pr� verifica��o!";
	static const std::string _ERROR_JIT_CREATE_ASMJIT_RETURN_ERROR = "Erro ao criar um jit em tempo de execu��o, biblioteca asmjit n�o conseguiu criar mem�ria executavel!";
	static const std::string _ERROR_JIT_CREATE_PRE_JIT_NOT_FOUND = "Erro ao criar um jit em tempo de execu��o, nenhum comando equivalente encontrado na pr� verifica��o!";


#endif /* LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_ */
