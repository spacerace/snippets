#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <inttypes.h>
#include <sys/types.h>

int main(){
	uint32_t i, len;
	
	char password[256];
	
	MD5_CTX context;
	
	unsigned char digest[16];
	
	printf("please enter your string, maximum of 255 chars.\n");
	scanf("%s", password);
	len = strlen (password);

	MD5_Init(&context);
	MD5_Update (&context, password, len);
	MD5_Final(digest, &context);

	printf ("MD5(\"%s\") = ", password);
	for (i = 0; i < 16; i++) {
		printf ("%02x", digest[i]);
	}
	printf ("\n");
	return 0;
}

