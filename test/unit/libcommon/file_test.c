#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#ifndef WIN32
#  include <unistd.h>
#endif
#include <stdlib.h>

#include "mosquitto.h"

#define ALLOW_SYMLINKS "MOSQUITTO_UNSAFE_ALLOW_SYMLINKS"

#ifndef WIN32
static bool symlink_create(void)
{
	FILE *fptr = mosquitto_fopen("libcommon_test", "rb", false);

	/* Verify we are in the right path */
	CU_ASSERT_PTR_NOT_NULL(fptr);
	if(!fptr){
		return false;
	}
	fclose(fptr);

	int rc = symlink("libcommon_test", "libcommon_symlink");
	CU_ASSERT_EQUAL(rc, 0);
	return rc == 0?true:false;
}


static void symlink_remove(void)
{
	unlink("libcommon_symlink");
}
#endif


#ifndef WIN32
static void TEST_restrict_read_default(void)
{
	FILE *fptr;

	if(!symlink_create()){
		return;
	}
	unsetenv(ALLOW_SYMLINKS);

	/* No restrict read, so symlink ok */
	fptr = mosquitto_fopen("libcommon_symlink", "rb", false);
	CU_ASSERT_PTR_NOT_NULL(fptr);
	if(fptr){
		fclose(fptr);
	}

	/* Restricted read, so symlink not allowed */
	fptr = mosquitto_fopen("libcommon_symlink", "rb", true);
	CU_ASSERT_PTR_NULL(fptr);
	if(fptr){
		fclose(fptr);
	}

	symlink_remove();
}


static void TEST_restrict_read_with_symlinks(void)
{
	FILE *fptr;

	if(!symlink_create()){
		return;
	}

	int rc = setenv(ALLOW_SYMLINKS, "1", true);
	CU_ASSERT_EQUAL(rc, 0);

	/* No restrict read, so symlink ok */
	fptr = mosquitto_fopen("libcommon_symlink", "rb", false);
	CU_ASSERT_PTR_NOT_NULL(fptr);
	if(fptr){
		fclose(fptr);
	}

	/* Restricted read but with override so symlink ok */
	fptr = mosquitto_fopen("libcommon_symlink", "rb", true);
	CU_ASSERT_PTR_NOT_NULL(fptr);
	if(fptr){
		fclose(fptr);
	}

	symlink_remove();
	unsetenv(ALLOW_SYMLINKS);
}
#endif


/* ========================================================================
 * TEST SUITE SETUP
 * ======================================================================== */


int init_file_tests(void)
{
	CU_pSuite test_suite = NULL;

	test_suite = CU_add_suite("file", NULL, NULL);
	if(!test_suite){
		printf("Error adding CUnit file test suite.\n");
		return 1;
	}

	if(0
#ifndef WIN32
			|| !CU_add_test(test_suite, "Restrict read default", TEST_restrict_read_default)
			|| !CU_add_test(test_suite, "Restrict read with symlinks", TEST_restrict_read_with_symlinks)
#endif
			){

		printf("Error adding file CUnit tests.\n");
		return 1;
	}

	return 0;
}
