using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NReadability;
using System.IO;
namespace Sipder
{
    public class Extractor:Worker
    {
        public List<string> urls;

        public string GetArticle(string filepath)
        {
            FileStream file =File.OpenRead(filepath);
            StreamReader reader = new StreamReader(file);
            string Html = reader.ReadToEnd();
            reader.Close();
            file.Close();
            bool success = false;
            NReadabilityTranscoder util = new NReadabilityTranscoder();
            string Article = util.Transcode(Html, out success);
            return Article;
        }

        public void GetTitle()
        {
            throw new System.NotImplementedException();
        }

        public void GetUrls()
        {
            throw new System.NotImplementedException();
        }
    }
}
