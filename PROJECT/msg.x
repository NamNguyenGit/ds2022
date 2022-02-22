struct numbers{
	char *method;
};

program COMP_PROG{
	version COMP_VERS{
		int comp(numbers)=1;
	}=1;
}=0x20000011;
