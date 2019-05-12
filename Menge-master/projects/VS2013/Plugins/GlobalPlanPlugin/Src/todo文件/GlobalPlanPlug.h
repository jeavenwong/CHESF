#pragma execution_character_set("utf-8")
#ifndef __DIJKSTRA_GL0BAL_PLUG_PLAN_H__
#define __DIJKSTRA_GL0BAL_PLUG_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/GlobalPlan/GlobalPlanFactory.h"

#include "GlobalPlanPlugConfig.h"

//TODO ���������Ͳ����
#define PLUGCLASS GlobalPlanPlugName
#define FACTORYPLUGCLASS GlobalPlanPlugFactoryName
#define PLUGNAME "���ģ�������"
#define PLUGDESC "���Ǹ��Ĳ��ģ��"


namespace Menge {

	namespace Agents {

		class  PLUGCLASS : public GlobalPlan {
		public:

			PLUGCLASS() : _planName(PLUGNAME) {
			//TODO �Զ��幹�캯��������������Ĭ������
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
				//TODO ����ʹ�ú꣬���Զ�������������Ϣ
				return PLUGDESC;
			};

			

		protected:

			GlobalPlan * instance() const { return new PLUGCLASS(); }
		};

	}	// namespace Agents
}	// namespace Menge
#endif	
