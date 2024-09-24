using System.Net.Mail;
using System.Net;
using System.Collections.Generic;
using System;

namespace SmtpService.SmtpService
{
    public class MailSenderComponent
    {
        private string SmtpServer { get; }
        private int Port { get; }
        private NetworkCredential MailCredential { get; }

        public MailSenderComponent(SmtpConfig initparameters)
        {
            SmtpServer = initparameters.SmtpServer;
            Port = initparameters.Port;
            MailCredential = initparameters.NetworkCredentials;
        }

        public void SendMail(MailAddress from, MailAddress to, MailAddress bcc, string subject, string body, List<Attachment> attachment)
        {
            if (string.IsNullOrEmpty(from.Address))
                throw new Exception("MAIL_FROM: ist leer");

            if (string.IsNullOrEmpty(to.Address))
                throw new Exception("MAIL_TO: ist leer");

            var message = new MailMessage();
            try
            {
                message.From = from;
                message.To.Add(to);
                message.Bcc.Add(bcc);
                message.Subject = subject;
                message.SubjectEncoding = System.Text.Encoding.UTF8;
                message.Body = body;
                message.IsBodyHtml = false;

                if (attachment != null)
                {
                    foreach (var att in attachment)
                    {
                        message.Attachments.Add(att);
                    }
                }

                using (var client = new SmtpClient()
                {
                    Host = this.SmtpServer,
                    Port = this.Port,
                    DeliveryMethod = SmtpDeliveryMethod.Network,
                    UseDefaultCredentials = false,
                    EnableSsl = true,
                    Credentials = this.MailCredential
                })
                {
                    client.Send(message);
                }

            }
            catch (Exception xpt)
            {
                var messageExc = xpt.Message;
                if (xpt.InnerException != null)
                {
                    messageExc += xpt.InnerException;
                    throw new Exception(messageExc);
                }

                throw new Exception(messageExc + " " + to);
            }

            //Logger.Write("BoiMailSender.SendMail(): Mail verschickt an " + message.To);
            return;
        }
    }
}