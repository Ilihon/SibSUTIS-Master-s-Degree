
using SmtpService;
using SmtpService.SmtpService;
using System;
using System.IO;

namespace AMS.Zerti.Service.Runner
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("Заполняются параметры отправки");
                var mailSettings = new MailSettings();
                mailSettings.SMTP_ENABLESSL = false;
                mailSettings.SMTP_SERVER = "smtp.mail.ru";
                mailSettings.SMTP_PORT = "587"; // 25 // 465 //ssl/tls
                mailSettings.SMTP_USERNAME = "ilia.burdukovskiy@mail.ru";
                mailSettings.SMTP_PASSWORD = "Tn3NdyjgkW0KZXQczEJu";
                mailSettings.BCC = "ilia.burdukovskiy@mail.ru";
                mailSettings.FROM = "ilia.burdukovskiy@mail.ru";

                Console.WriteLine("Создается сообщение");
                var data = new MailItem();
                data.Title = "Заголовок тестового письма";
                data.Body = "Тело тестового пиьса";
                data.Email = "ilia.burdukovskiy@mail.ru";
                //data.Email = "ilihon.vedington@yandex.ru";
                //data.Email = "ilia.burdukovskiy@gmail.com";


                Console.WriteLine("Прикрепляются файлы");
                data.Files = new System.Collections.Generic.List<FileModel>();

                // pdf file
                var file = new FileModel();
                file.DataType = "aplication/pdf";
                file.Data = File.ReadAllBytes("file1.pdf");
                file.Name = "file1.pdf";
                data.Files.Add(file);

                // rar file
                file = new FileModel();
                file.DataType = "aplication/rar";
                file.Data = File.ReadAllBytes("file2.rar");
                file.Name = "file2.rar";
                data.Files.Add(file);
               
                // png file
                file = new FileModel();
                file.DataType = "aplication/jpg";
                file.Data = File.ReadAllBytes("file3.jpg");
                file.Name = "file3.jpg";
                data.Files.Add(file);
                
                Console.WriteLine("Отправка");
                var service = new MailingService(mailSettings);
                service.SendMail(data);
                Console.WriteLine("Сообщение успешно отправлено");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Сообщение не отправлено");
                Console.WriteLine(ex.ToString());
            }
        }
    }
}