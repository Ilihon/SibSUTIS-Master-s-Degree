using SmtpService.SmtpService;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;

namespace SmtpService
{
    public class BaseMailingService
    {
        protected MailSenderComponent mEmailClient;
        protected MailSettings mMailSettings;

        public BaseMailingService(MailSettings mailSettings)
        {
            try
            {
                mMailSettings = mailSettings;
                var smtpConfig = new SmtpConfig(
                    mailSettings.SMTP_SERVER, int.Parse(mailSettings.SMTP_PORT),
                    mailSettings.SMTP_USERNAME, mailSettings.SMTP_PASSWORD);

                mEmailClient = new MailSenderComponent(smtpConfig);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                throw;
            }

        }
    }
}
