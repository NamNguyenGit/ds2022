/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "msg.h"

int *
comp_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	printf("Client connect!!!\n");
	printf("receive %s\n", argp->method);
	result = *argp->method;
	return &result;
}
