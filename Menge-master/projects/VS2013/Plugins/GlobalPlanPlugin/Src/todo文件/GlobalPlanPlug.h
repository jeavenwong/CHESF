#pragma execution_character_set("utf-8")
#ifndef __DIJKSTRA_GL0BAL_PLUG_PLAN_H__
#define __DIJKSTRA_GL0BAL_PLUG_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/GlobalPlan/GlobalPlanFactory.h"

#include "GlobalPlanPlugConfig.h"

//TODO 定义类名和插件名
#define PLUGCLASS GlobalPlanPlugName
#define FACTORYPLUGCLASS GlobalPlanPlugFactoryName
#define PLUGNAME "插件模块的名称"
#define PLUGDESC "这是个的插件模版"


namespace Menge {

	namespace Agents {

		class  PLUGCLASS : public GlobalPlan {
		public:

			PLUGCLASS() : _planName(PLUGNAME) {
			//TODO 自定义构造函数，可用于设置默认属性
			}


			virtual std::string getPlan() { return _planName; }


			virtual std::vector<Menge::Math::Vector2>  getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
			                                                         std::map<int, Menge::Agents::Path > pathMapTemp,
			                                                         std::vector<Agents::Map *> _maps,
			                                                         Math::Vector2 agentPos,
			                                                         int id
			) const;

			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				                       std::vector<BaseAgent *> agents
			) const;

		protected:

			std::string _planName;
		};


		class FACTORYPLUGCLASS : public GlobalPlanFactory {
		public:

			FACTORYPLUGCLASS();


			virtual const char * name() const { return PLUGNAME; }

			virtual const char * description() const {
				//TODO 若不使用宏，可自定义插件的描述信息
				return PLUGDESC;
			};

			

		protected:

			GlobalPlan * instance() const { return new PLUGCLASS(); }
		};

	}	// namespace Agents
}	// namespace Menge
#endif	
