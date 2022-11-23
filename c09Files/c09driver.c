https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Test driver for Rational.c
//
// Invocation:  ./driver [-repeat]
//
// If the -repeat switch is omitted, the driver will create a random set
// of test cases, and save the random seed in a file; if the -repeat
// switch is present, the driver will open the previously-created seed
// file and use that to reproduce the previous set of test cases.
//
// Either way, a summary of the results of the testing will be written
// to a file named c08Results.txt.  Results of testing individual 
// features are available in separate text files.
//
// Library headers for various features:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
// "Local" headers for testing code and solution:
#include "Rational.h"
#include "TestRational.h"

// Name for file containing test results:
static char* resultsFileName = "c09Results.txt";

int main(int argc, char** argv) {
   
   // Validate number of parameters:
   if ( argc != 1 && argc != 2 ) {
		printf("Invocation:  driver [-repeat]\n");
		exit(1);
	}
	
	// Variable for random seed:
   unsigned int Seed = 0;
   
	// Determine the mode of operation:
	if ( argc == 2 && strcmp(argv[1], "-repeat") == 0 ) {
      FILE* fp = fopen("seed.txt", "r");
      if ( fp == NULL ) {
			printf("Could not open seed file... run without -repeat.\n");
			exit(2);
		}
      fscanf(fp, "%u", &Seed);
      fclose(fp);
	}
	else if ( argc == 2 ) {
		printf("Unrecognized option: %s\n", argv[1]);
		exit(3);
	}
	else {
      Seed = time(NULL);
      FILE* fp = fopen("seed.txt", "w");
      fprintf(fp, "%u\n", Seed);
      fclose(fp);
	}

   // Step for varying the random seed:
   unsigned int seedStep = Seed % 10000;
   // Local variables for obtaining score information from the test code:
   uint32_t scoreThisTest = 0;
   uint32_t maxThisTest = 0;
   uint32_t totalScore = 0;
   uint32_t maxScore = 0;
   // File for the test summary:
   FILE* Summary = fopen(resultsFileName, "w");

   // Seed the random generator for the first test:
   srand(Seed);
   
   int testNum = 1;
   bool success = testCreate(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Create(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;
   if ( !success ) {
      fprintf(Summary, "Failed test of Rational_Create().\n");
      fprintf(Summary, "Aborting remaining tests.\n\n");
      fprintf(Summary, "Total score: %"PRIu32" / %"PRIu32"\n", totalScore, maxScore);
      fclose(Summary);
      return 0;
   }

   // Reseed the random generator for each test:
   srand(Seed + seedStep);
   success = testNegate(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Negate(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testAbsVal(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_AbsVal(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testCeiling(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Ceiling(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testAdd(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Add(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testMultiply(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Multiply(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testDivide(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Divide(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testEQ(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_Equals(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   srand(Seed + seedStep);
   success = testLT(&scoreThisTest, &maxThisTest);
   fprintf(Summary, "%3d >> Score for Rational_LessThan(): %"PRIu32" / %"PRIu32"\n",
           testNum, scoreThisTest, maxThisTest);
   totalScore += scoreThisTest;
   maxScore += maxThisTest;
   testNum++;

   fprintf(Summary, "\nTotal score: %"PRIu32" / %"PRIu32"\n", totalScore, maxScore);
   
   fclose(Summary);
   return 0;
}

