using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sipder.DataModel
{
    public enum SiteType
    {
        Blog = 0,//博客类
        Video,//视频类
        News,//新闻类
        Music,//音乐网站
        PhtotGallery,//相册类
        Mall,//商城类
        Weibo,//微博类
        SNS//社交类
    };
    public enum PageType
    {
        Index = 0,//首页
        SubIndex,//子导航
        Detail
    }
    public class HtmlDocInfo
    {
        private int _DocId;
        private List<string> _AttechMent;
        private string _HtmlURL;
        private List<string> _OutURLs;
        private List<string> _InURLs;
        private string _LocalPath;
    }
}
