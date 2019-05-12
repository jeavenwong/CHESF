/*

License

Menge
Copyright ?and trademark ?2012-14 University of North Carolina at Chapel Hill. 
All rights reserved.

Permission to use, copy, modify, and distribute this software and its documentation 
for educational, research, and non-profit purposes, without fee, and without a 
written agreement is hereby granted, provided that the above copyright notice, 
this paragraph, and the following four paragraphs appear in all copies.

This software program and documentation are copyrighted by the University of North 
Carolina at Chapel Hill. The software program and documentation are supplied "as is," 
without any accompanying services from the University of North Carolina at Chapel 
Hill or the authors. The University of North Carolina at Chapel Hill and the 
authors do not warrant that the operation of the program will be uninterrupted 
or error-free. The end-user understands that the program was developed for research 
purposes and is advised not to rely exclusively on the program for any reason.

IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS 
BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS 
DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE 
AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY 
DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY STATUTORY WARRANTY 
OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS HAVE NO OBLIGATIONS 
TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

Any questions or comments should be sent to the authors {menge,geom}@cs.unc.edu

*/

#include <Windows.h>
#include "MengeCore/Runtime/Logger.h"
#include "MengeCore/Runtime/os.h"

#include "MengeCore/EnvironmentalChange/EnvironmentalChangeDatabase.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChangeFactory.h"
#include "MengeCore/EnvironmentalChange/MapChange.h"
#include "MengeCore/EnvironmentalChange/SpecialAreaChange.h"
#include "MengeCore/EnvironmentalChange/NewObstacleChange.h"


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
		ElementDB< Agents::EnvironmentalChangeFactory, Agents::EnvironmentalChange >::getElementName() {
		return "initial state selector";
	}

	/*! 
	 *	@brief		Initialization of built in database elements.
	 */
	template <>
	void ElementDB< Agents::EnvironmentalChangeFactory, Agents::EnvironmentalChange >::addBuiltins() {
		addFactory( new Agents::MapChangeFactory() );
		addFactory(new Agents::SpecialAreaChangeFactory());
		addFactory(new Agents::NewObstacleChangeFactory());
		
		TCHAR chCurDir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, chCurDir);
		SetCurrentDirectory(LPCSTR("D:\\Menge-master\\Exe\\DllPlugins\\EnvironmentalChange\\"));


		std::string pluginFolder = "D:\\Menge-master\\Exe\\DllPlugins\\EnvironmentalChange";
		StringList files;
#ifdef _MSC_VER
		std::string extension("*.dll");
#else
		std::string extension("*.so");
#endif
		if (!os::listdir(pluginFolder, files, extension)) {
			return ;
		}
		StringListCItr itr = files.begin();
		for (; itr != files.end(); ++itr) {
			using pExport = Menge::Agents::EnvironmentalChangeFactory* (*)(void); // 定义指向导出函数的指针类型
			HINSTANCE hDll = LoadLibrary((*itr).c_str());// 加载DLL库文件，DLL名称和路径用自己的
			if (hDll == NULL){
				std::cout << "load dll fail \n";
			}
			else {
			       pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
			       if (Get == NULL){
					std::cout << "load address fail \n";
				   }
				   else {
					Menge::Agents::EnvironmentalChangeFactory* t = Get();// 调用导出函数获得抽象类指针
					addFactory(t);
				   }
			    }
		    }
		SetCurrentDirectory(chCurDir);

		//delete t; // 释放DLL中生成的对象
		//FreeLibrary(hDll); //释放库句柄
		//system("pause");


	}

}	// namespace Menge

#endif	 // DOXYGEN_SHOULD_SKIP_THIS
