//
//  Modified from PosixAsyncService.cpp
//
//  Created by Robert Bu on 12/8/14.
//  Copyright (c) 2014 Robert Bu. All rights reserved.
//

#include "PosixAsyncService.h"

namespace vl {

    namespace presentation {

        namespace x11cairo {

            using namespace collections;

            PosixAsyncService::TaskItem::TaskItem():
		            semaphore(0)
            {

            }

            PosixAsyncService::TaskItem::TaskItem(Semaphore* _semaphore, const Func<void()>& _proc):
		            semaphore(_semaphore),
		            proc(_proc)
            {

            }

            PosixAsyncService::TaskItem::~TaskItem()
            {

            }

            PosixAsyncService::DelayItem::DelayItem(PosixAsyncService* _service, const Func<void()>& _proc, bool _executeInMainThread, vint milliseconds):
		            service(_service),
		            proc(_proc),
		            status(INativeDelay::Pending),
		            executeTime(DateTime::LocalTime().Forward(milliseconds)),
		            executeInMainThread(_executeInMainThread)
            {

            }

            PosixAsyncService::DelayItem::~DelayItem()
            {

            }

            INativeDelay::ExecuteStatus PosixAsyncService::DelayItem::GetStatus()
            {
	            return status;
            }

            bool PosixAsyncService::DelayItem::Delay(vint milliseconds)
            {
	            SPIN_LOCK(service->taskListLock)
	            {
		            if(status==INativeDelay::Pending)
		            {
			            executeTime=DateTime::LocalTime().Forward(milliseconds);
			            return true;
		            }
	            }
	            return false;
            }

            bool PosixAsyncService::DelayItem::Cancel()
            {
	            SPIN_LOCK(service->taskListLock)
	            {
		            if(status==INativeDelay::Pending)
		            {
			            if(service->delayItems.Remove(this))
			            {
				            status=INativeDelay::Canceled;
				            return true;
			            }
		            }
	            }
	            return false;
            }

            PosixAsyncService::PosixAsyncService():
		            mainThreadId(Thread::GetCurrentThreadId())
            {

            }

            PosixAsyncService::~PosixAsyncService()
            {

            }

            void PosixAsyncService::ExecuteAsyncTasks()
            {
	            DateTime now = DateTime::LocalTime();
	            Array<TaskItem> items;
	            List<Ptr<DelayItem>> executableDelayItems;

	            SPIN_LOCK(taskListLock)
	            {
		            CopyFrom(items, taskItems);
		            taskItems.RemoveRange(0, items.Count());
		            for(vint i = delayItems.Count()-1;i>=0;i--)
		            {
			            Ptr<DelayItem> item = delayItems[i];
			            if(now.filetime >= item->executeTime.filetime)
			            {
				            item->status = INativeDelay::Executing;
				            executableDelayItems.Add(item);
				            delayItems.RemoveAt(i);
			            }
		            }
	            }

	            FOREACH(TaskItem, item, items)
	            {
		            item.proc();
		            if(item.semaphore)
		            {
			            item.semaphore->Release();
		            }
	            }

	            FOREACH(Ptr<DelayItem>, item, executableDelayItems)
	            {
		            if(item->executeInMainThread)
		            {
			            item->proc();
			            item->status=INativeDelay::Executed;
		            }
		            else
		            {
			            InvokeAsync([=]()
			            {
			                item->proc();
			                item->status=INativeDelay::Executed;
			            });
		            }
	            }
            }

            bool PosixAsyncService::IsInMainThread()
            {
	            return Thread::GetCurrentThreadId() == mainThreadId;
            }

            void PosixAsyncService::InvokeAsync(const Func<void()>& proc)
            {
	            ThreadPoolLite::Queue(proc);
            }

            void PosixAsyncService::InvokeInMainThread(const Func<void()>& proc)
            {
	            SPIN_LOCK(taskListLock)
	            {
		            TaskItem item(0, proc);
		            taskItems.Add(item);
	            }
            }

            bool PosixAsyncService::InvokeInMainThreadAndWait(const Func<void()>& proc, vint milliseconds)
            {
	            Semaphore* semaphore = new Semaphore();
	            semaphore->Create(0, 1);

	            TaskItem item(semaphore, proc);
	            SPIN_LOCK(taskListLock)
	            {
		            taskItems.Add(item);
	            }

	            // todo, if semphoare fails to wait for some reason
	            // taskItems will corrupt
	            return semaphore->Wait();

//                if(milliseconds < 0)
//                {
//                    return semaphore.Wait();
//                }
//                else
//                {
//                    // todo
//                    return false;
//                    //return semaphore.WaitForTime(milliseconds);
//                }
            }

            Ptr<INativeDelay> PosixAsyncService::DelayExecute(const Func<void()>& proc, vint milliseconds)
            {
	            Ptr<DelayItem> delay;
	            SPIN_LOCK(taskListLock)
	            {
		            delay = new DelayItem(this, proc, false, milliseconds);
		            delayItems.Add(delay);
	            }
	            return delay;
            }

            Ptr<INativeDelay> PosixAsyncService::DelayExecuteInMainThread(const Func<void()>& proc, vint milliseconds)
            {
	            Ptr<DelayItem> delay;
	            SPIN_LOCK(taskListLock)
	            {
		            delay = new DelayItem(this, proc, true, milliseconds);
		            delayItems.Add(delay);
	            }
	            return delay;
            }


        }

    }

}