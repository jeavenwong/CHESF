#include <Windows.h>
#include "MengeCore/Runtime/Logger.h"
#include "MengeCore/Runtime/os.h"

#include "MengeCore/OperationPlan/OperationPlanDatabase.h"
#include "MengeCore/OperationPlan/ORCA.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace Menge {

	// Specialization
	/*!
	 *	@brief		Reports the database name.
	 *
	 *	@returns	The string representation of the database name.
	 */
	template <>
	std::string
		ElementDB< Agents::OperationPlanFactory, Agents::OperationPlan >::getElementName() {
		return "initial state selector";
	}

	/*! 
	 *	@brief		Initialization of built in database elements.
	 */
	template <>
	void ElementDB< Agents::OperationPlanFactory, Agents::OperationPlan >::addBuiltins() {
		addFactory( new Agents::OperationORCAPlanFactory() );
	
		
		TCHAR chCurDir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, chCurDir);
		SetCurrentDirectory(LPCSTR("D:\\Menge-master\\Exe\\DllPlugins\\OperationPlan"));

		std::string pluginFolder = "D:\\Menge-master\\Exe\\DllPlugins\\OperationPlan";
		StringList files;
#ifdef _MSC_VER
		std::string extension("*.dll");
#else
		std::string extension("*.so");
#endif
		if (!os::listdir(pluginFolder, files, extension)) {
			return;
		}
		StringListCItr itr = files.begin();
		for (; itr != files.end(); ++itr) {
			using pExport = Menge::Agents::OperationPlanFactory* (*)(void); // 定义指向导出函数的指针类型
			HINSTANCE hDll = LoadLibrary((*itr).c_str());// 加载DLL库文件，DLL名称和路径用自己的
			if (hDll == NULL) {
				std::cout << "load dll fail \n";
			}
			else {
				pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
				if (Get == NULL) {
					std::cout << "load address fail \n";
				}
				else {
					Menge::Agents::OperationPlanFactory* t = Get();// 调用导出函数获得抽象类指针
					addFactory(t);
				}
			}
		}
		SetCurrentDirectory(chCurDir);
	}

}	// namespace Menge

#endif	 // DOXYGEN_SHOULD_SKIP_THIS
