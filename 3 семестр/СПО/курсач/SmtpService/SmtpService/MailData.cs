using System.Collections.Generic;
using System.Net.Mail;

namespace SmtpService.SmtpService
{
    public class MailData
    {
        public string ToEmail { get; set; }
        public string Subject { get; set; }
        public string Body { get; set; }
        public List<Attachment> AttachmentData { get; set; } = new List<Attachment>();
        public string BccEmail { get; set; }
    }
}
