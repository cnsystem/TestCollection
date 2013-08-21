using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sipder.DataModel
{

    public class FectcherUrl
    {
        public FectcherUrl(string url)
        {
            this.Url = url;
        }
        public static int MostFailedCount = 3;
        public string Url { get; set; }
        public bool isFinish { get; set; }
        public int FailedConut { get; set; }
        public string LocalFilePath { get; set; }
    }
}
