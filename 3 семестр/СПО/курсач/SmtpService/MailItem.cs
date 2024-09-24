using System.Collections.Generic;

namespace SmtpService
{
    public class MailItem
    {
        public string Email { get; set; }
        public string Title { get; set; }
        public string Body { get; set; }
        public List<FileModel> Files { get; set; }
    }
    public class FileModel
    {
        public string Name { get; set; }
        public byte[] Data { get; set; }
        public string DataType { get; set; }
    }
}
