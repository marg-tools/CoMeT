/**
 * scheduler_open
 * This header implements open scheduler functionality. The class is extended from default "Pinned" scheduler.
 */


#ifndef __SCHEDULER_OPEN_H
#define __SCHEDULER_OPEN_H

#include <vector>

#include "scheduler_pinned_base.h"
#include "performance_counters.h"
#include "policies/dvfspolicy.h"
#include "policies/mappingpolicy.h"
#include "policies/migrationpolicy.h"
#include "policies/dramLowpower.h"
#include "policies/drampolicy.h"


//This data structure maintains the state of the tasks.
struct openTask {
	openTask(int taskIDInput, String taskNameInput, int taskCoreRequirement)
	: taskID(taskIDInput), taskName(taskNameInput), taskCoreRequirement(taskCoreRequirement) {}

	int taskID;
	String taskName;
	bool waitingToSchedule = true;
	bool waitingInQueue = false;
	bool active = false;
	bool completed = false;
	int taskCoreRequirement;
	UInt64 taskArrivalTime;
	UInt64 taskStartTime;
	UInt64 taskDepartureTime;
};

//This data structure maintains the state of the cores.
struct systemCore {
	systemCore(int coreIDInput) : coreID(coreIDInput) {}

	int coreID;
	int assignedTaskID = -1; // -1 means core assigned to no task
	int assignedThreadID = -1;// -1 means core assigned to no thread.
};

class SchedulerOpen : public SchedulerPinnedBase {

	public:
		SchedulerOpen (ThreadManager *thread_manager); //This function is the constructor for Open System Scheduler.
		virtual void periodic(SubsecondTime time);
		virtual void threadSetInitialAffinity(thread_id_t thread_id);
		virtual bool threadSetAffinity(thread_id_t calling_thread_id, thread_id_t thread_id, size_t cpusetsize, const cpu_set_t *mask);
		virtual core_id_t threadCreate(thread_id_t thread_id);
		virtual void threadExit(thread_id_t thread_id, SubsecondTime time);
	private:
		int numberOfTasks;
		int numberOfCores;
		int coresInX;
		int coresInY;
		int coresInZ;
		int numberOfBanks;
		int banksInX;
		int banksInY;
		int banksInZ;
		int numberOfComponents;

		PerformanceCounters *performanceCounters;

		// scheduling
		std::vector <openTask> openTasks;
		std::vector <systemCore> systemCores;
		String queuePolicy;
		String distribution;
		int arrivalRate;
		int arrivalInterval;

		void fetchTasksIntoQueue (SubsecondTime time);
		int coreRequirementTranslation(String compositionString);
		int taskFrontOfQueue();
		int numberOfFreeCores();
		int numberOfTasksInQueue();
		int numberOfTasksWaitingToSchedule();
		int numberOfTasksCompleted();
		int numberOfActiveTasks();
		int totalCoreRequirementsOfActiveTasks();

		// mapping
		MappingPolicy *mappingPolicy = NULL;
		long mappingEpoch;
		void initMappingPolicy(String policyName);
		bool executeMappingPolicy(int taskID, SubsecondTime time);
		int getCoreNb(int x, int y, int z);
		bool isAssignedToTask(int coreId);
		bool isAssignedToThread(int coreId);

		// DVFS
		DVFSPolicy *dvfsPolicy = NULL;
		long dvfsEpoch;
		void initDVFSPolicy(String policyName);
		void executeDVFSPolicy();
		void setFrequency(int coreCounter, int frequency);
		int minFrequency;
		int maxFrequency;
		int frequencyStepSize;

		// Dram
		DramPolicy *dramPolicy = NULL;
		long dramEpoch;
		void initDramPolicy(String policyName);
		void executeDramPolicy();
		void setMemBankMode(int bankNr, int mode);

		// migration
		MigrationPolicy *migrationPolicy = NULL;
		long migrationEpoch;
		void initMigrationPolicy(String policyName);
		void executeMigrationPolicy(SubsecondTime time);
		void migrateThread(thread_id_t thread_id, core_id_t core_id);

		// Reliability
		bool rlb_enabled;
		bool subcore_enabled;
		float vth;
		float delta_v_scale_factor;
		std::vector<int> maxFrequencyDynamic;
		void checkFrequencies();

		std::string formatTime(SubsecondTime time);

		core_id_t getNextCore(core_id_t core_first);
		core_id_t getFreeCore(core_id_t core_first);

		const int m_interleaving;
		std::vector<bool> m_core_mask;
		core_id_t m_next_core;

		int setAffinity (thread_id_t thread_id);
		bool schedule (int taskID, bool isInitialCall, SubsecondTime time);
};

#endif // __SCHEDULER_OPEN_H
