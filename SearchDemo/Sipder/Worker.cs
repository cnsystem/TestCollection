using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;
namespace Sipder
{
    public enum WorkStatus
    {
        Initial = 1,
        Available,
        Working,
        Finishing,
    }
    public delegate void WorkerStatusSwitch(object sender, object args);

    public abstract class Worker
    {
        protected WorkStatus _Status;
        protected Thread WorkThread;

        public virtual void StartWork()
        {
            _Status = WorkStatus.Working;
        }

        public virtual void StopWork()
        {
            _Status = WorkStatus.Finishing;
        }

        public virtual void StartWithThread()
        {
            ThreadStart start = new ThreadStart(StartWork);
            WorkThread = new Thread(start);
            WorkThread.Start();
        }
    }
}
