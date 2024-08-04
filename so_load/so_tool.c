#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#include <openssl/evp.h>

char md[128] = {0};


int CalcSha(const char *file)
{
    char buf[1024];
    int nread;
    int mdmaxlen = 128;
    EVP_MD_CTX *ctx;

    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        return -1;
    }
    ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, EVP_sha256());
    while ((nread = read(fd, buf, 1024)) > 0) {
        EVP_DigestUpdate(ctx, buf, nread);
    }
    EVP_DigestFinal(ctx, md, &mdmaxlen);
    EVP_MD_CTX_free(ctx);
    return !((nread == 0) && (mdmaxlen == 32));
}

int CalcSig(const char *key)
{
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: %s privkey so\n", argv[0]);
        return -1;
    }

    if ((access(argv[1], R_OK) != 0) || (access(argv[2], R_OK) != 0)) {
        printf("%s/%s not readable\n", argv[1], argv[2]);
        return -1;
    }

    if (CalcSha((const char *)argv[2]) != 0) {
        printf("md5 calc error\n");
        return -1;
    }
    return 0;
}