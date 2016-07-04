#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define F1	"a.txt"
#define F2	"b.txt"

int main() {
	struct stat attribut;

	stat(F1, &attribut);

	printf("%d\n", attribut.st_mtime);

}
