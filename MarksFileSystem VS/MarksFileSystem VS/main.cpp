#include <stdio.h>
#include "MarksFileSystem.h"

int main()
{
	printf("IT BUILDS!\ngood job mark\n:)");
	getchar();

	MFSDrive drive;

	drive.formatDrive(1000000, 200);

}