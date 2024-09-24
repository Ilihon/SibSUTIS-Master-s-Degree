using SmtpService.SmtpService;
using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.IO;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace SmtpService
{
    public class MailingService : BaseMailingService
    {
        public MailingService(MailSettings mailSettings) : base(mailSettings)
        {
        }
        public void SendMail(MailItem item)
        {
            var to = item.Email;
            var attachmentList = AddAttachmentList(item).GetAwaiter().GetResult();

            mEmailClient.SendMail(new MailAddress(mMailSettings.FROM), new MailAddress(to), new MailAddress(mMailSettings.BCC),
                item.Title, item.Body, attachmentList);
        }

        private async Task<List<Attachment>> AddAttachmentList(MailItem item)
        {
            List<Attachment> attachmentList = new List<Attachment>();
            if (item.Files?.Count() > 0)
            {
                foreach (var doc in item.Files)
                {
                    var file = doc.Data;
                    attachmentList.Add(new Attachment(new MemoryStream(file), doc.Name, doc.DataType));
                }
            }

            return attachmentList;
        }
    }
}
