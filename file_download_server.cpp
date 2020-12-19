#include "c_public/tcp_server.h"
#include <stdio.h>
#include <string>

class DownloadFileServer : public TcpServer
{
    protected:
    void OnReceiveData(int connect_fd, char *data, int size)
    {
        int content_max_size = 1024;
        char header[1024];
        char content[1024];
        sprintf(header, HTTP_DOWNLOAD_RESPONSE_HEADER);
        Send(connect_fd, header, strlen(header));

        FILE *fp = fopen(filename, "r");
        bool isEOF = false;
        while (!isEOF)
        {
            int size;
            for (size = 0; size < content_max_size; size++)
            {
                int c = fgetc(fp);
                isEOF = c == EOF;
                if (c == EOF) break;
                content[size] = (unsigned char) c;
            }
            Send(connect_fd, content, size);
        }
        fclose(fp);
    }

    public:
    char filename[1024];
};

int main(int argc, char* argv[])
{
    DownloadFileServer server;
    scanf("%s", server.filename);
    server.Run(4000);
    return 0;
}