#include <stdio.h>

int main()
{
	const char filename[] = "presidents.dat";
	struct person {
		char name[32];
		int inauguration;
		int age;
	} president;
	int x;
	FILE *fp;

	/* open the file */
	fp = fopen(filename,"r");
	if( fp == NULL )
	{
		printf("Unable to open %s\n",filename);
		return(1);
	}

	/* read records from back to front */
	fseek(fp, 0, SEEK_END); /* go to the end of the file */
	while( ftell(fp) > 0 ) /* while we are not at the beginning */
	{
		/* move back one record */
		fseek(fp, - (long)sizeof(struct person), SEEK_CUR);
		/* read the record */
		x = fread(&president, sizeof(struct person), 1, fp);
		if( x != 1 )
		{
			printf("Error reading record\n");
			fclose(fp);
			return(2);
		}
		/* display the record */
		printf("%-20s Inaugurated: %4d Age: %2d\n",
			president.name,
			president.inauguration,
			president.age);
	}
	/* clean-up */
	fclose(fp);
	return(0);
}


