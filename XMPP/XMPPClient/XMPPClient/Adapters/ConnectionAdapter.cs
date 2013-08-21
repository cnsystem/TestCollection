using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using agsXMPP;
namespace XMPPClient.Adapters
{
    public class ConnectionAdapter
    {
        public agsXMPP.XmppClientConnection _connection;
        public event XMPPDelegate _onConnect;
        public ConnectionAdapter()
        {
            _connection = new XmppClientConnection(AppConfig.ServerAddr, AppConfig.ServerPort);
            _connection.OnReadXml += new XmlHandler(_connection_OnReadXml);
            _connection.OnWriteXml += new XmlHandler(_connection_OnWriteXml);                      
        }

        void _connection_OnWriteXml(object sender, string xml)
        {
            Console.WriteLine("*************************Send Data*********************************");
            Console.WriteLine(xml);
            Console.WriteLine("***********************Send Data End*******************************");
        }

        void _connection_OnReadXml(object sender, string xml)
        {
            Console.WriteLine("*************************Read Data*********************************");
            Console.WriteLine(xml);
            Console.WriteLine("***********************Read Data End*******************************");
        }
        public void connect()
        {            
            _connection.SocketConnect();
            _connection.Open();
            
            //_connection.SocketOnConnect
        }
        public void Login(string username, string password)
        {
            _connection.Open(username, password);
        }
        public void Register(string username, string password,string email)
        {
            agsXMPP.protocol.iq.register.Register resgiterItem = new agsXMPP.protocol.iq.register.Register(username, password);
            resgiterItem.Email = email;
            agsXMPP.protocol.iq.register.RegisterIq r = new agsXMPP.protocol.iq.register.RegisterIq();
            _connection.Open(username, password);
        }
    }
    public delegate void XMPPDelegate (Object sender);
}
