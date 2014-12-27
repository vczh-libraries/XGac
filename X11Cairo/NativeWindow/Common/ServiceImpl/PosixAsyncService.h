//  Modified from PosixAsyncService.h
//
//  Created by Robert Bu on 12/8/14.
//  Copyright (c) 2014 Robert Bu. All rights reserved.
//

#ifndef __UNIX_ASYNC_SERVICE_H
#define __UNIX_ASYNC_SERVICE_H

#include <GacUI.h>

namespace vl {

    namespace presentation {

        namespace x11cairo {

            class PosixAsyncService : public INativeAsyncService
            {
            protected:
	            struct TaskItem
	            {
		            Semaphore*              semaphore;
		            Func<void()>            proc;

		            TaskItem();
		            TaskItem(Semaphore* _semaphore, const Func<void()>& _proc);
		            ~TaskItem();
	            };

	            class DelayItem: public Object, public INativeDelay
	            {
	            public:
		            DelayItem(PosixAsyncService* _service, const Func<void()>& _proc, bool _executeInMainThread, vint milliseconds);
		            ~DelayItem();

		            PosixAsyncService*      service;
		            Func<void()>            proc;
		            ExecuteStatus           status;
		            DateTime                executeTime;
		            bool                    executeInMainThread;

		            ExecuteStatus           GetStatus() override;
		            bool                    Delay(vint milliseconds) override;
		            bool                    Cancel() override;
	            };

	            collections::List<TaskItem>				taskItems;
	            collections::List<Ptr<DelayItem>>		delayItems;
	            SpinLock								taskListLock;
	            vint                                    mainThreadId;

            public:
	            PosixAsyncService();
	            ~PosixAsyncService();

	            void                ExecuteAsyncTasks();
	            bool                IsInMainThread()override;
	            void                InvokeAsync(const Func<void()>& proc)override;
	            void                InvokeInMainThread(const Func<void()>& proc)override;
	            bool                InvokeInMainThreadAndWait(const Func<void()>& proc, vint milliseconds)override;
	            Ptr<INativeDelay>   DelayExecute(const Func<void()>& proc, vint milliseconds)override;
	            Ptr<INativeDelay>   DelayExecuteInMainThread(const Func<void()>& proc, vint milliseconds)override;
            };
        }
    }
}

#endif