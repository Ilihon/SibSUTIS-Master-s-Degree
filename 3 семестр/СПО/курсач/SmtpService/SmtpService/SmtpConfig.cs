using System.Net;

namespace SmtpService.SmtpService
{
    public class SmtpConfig
    {
        public string SmtpServer { get; private set; }
        public NetworkCredential NetworkCredentials { get; set; }
        public int Port { get; set; }

        public SmtpConfig(string smtpServer, int smptPort, string username, string passwort)
        {
            SmtpServer = smtpServer;
            Port = smptPort;
            NetworkCredentials = new NetworkCredential(username, passwort);
        }
    }
}
