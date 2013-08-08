
#ifndef TESTMODULE_H_
#define TESTMODULE_H_

#include <memory>

#include <pthread.h>

#include "Module.h"
#include "Command.h"

class TestModule: public Module{
private:
	class TestModuleCommand;
	class CommandGetState;
	class CommandGetParams;
	class CommandSetParams;

	bool state;
	int interval;
	std::string name;

	pthread_mutex_t mutex_tm;
	pthread_t thread_tm;

	bool run;
	static void * tread_task(void * pthis);

public:

	TestModule(bool state_v = false, int interval_v = 1, const std::string & name_v = "testmodule");
	void set_name(const std::string & new_name);
	std::string get_name();
	void set_interval(int new_interval);
	int get_interval();
	bool get_state();
	~TestModule();

	void lock();
	void unlock();

	class Lock{
		friend class TestModule;
		TestModule * ptm;
		Lock(TestModule * ptmv);
		public:
		~Lock();
	};

	std::unique_ptr<TestModule::Lock> getLock();
};

class TestModule::TestModuleCommand : public Command{
protected:
	TestModule * ptm;

	virtual void parse_arguments(const std::string & arguments) = 0;

public:
	TestModuleCommand(TestModule * p_tm, const std::string & name_v = "testmodulecommand"): Command(name_v), ptm(p_tm) {}
	virtual std::shared_ptr<Command> clone() const = 0;
	virtual std::string invoke(const std::string & arguments) = 0;
	virtual ~TestModuleCommand() {}
};

#endif /* TESTMODULE_H_ */
