https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#! /bin/bash
#
#  Last modified:  April 10, 2019
#
#  This script must be executed in a directory that contains the grading harness
#  tar file (c08Files.tar) posted on the course website; that tar file must
#  contain the files:
#
#    driver.c
#    Rational.h
#    TestRational.h
#    TestRational.o
#
#  The directory must also contain your completed Rational.c file; we recommend
#  that you name that file yourPID.c, using your VT email PID as the first part
#  of the file name.
#
#  Invocation:  ./gradeC09.sh <name of your .c file>
#               e.g., ./gradeC09.sh wmcquain.c
#
#  A summary of the test results can be found in the file summary.txt.  There
#  will be a separate log file for each test phase that was completed, and an
#  overall report, named PID.txt if you followed the suggested naming convention.
#
#  Alternate invocation:  ./gradeC09.sh -clean
#
#  This will remove the files created by an earlier run of the grading script;
#  it's useful if you just want to start with a pristine environment.
#
#  Name of grading package file
gradingTar="c09Files.tar"

#  Rename for student file
renameC="Rational.c"

#  Names for directories
buildDir="build"

#   Names for log files created by this script:
buildLog="buildLog.txt"
testLog="testLog.txt"

#   Name for the executable
#exeName="c09"

#  Names for driver-generated test results files
scoreFile="c09Results.txt"
testFiles=("SetLog.txt" "NegateLog.txt" "AbsValLog.txt" "CeilingLog.txt" \
           "AddLog.txt" "DivideLog.txt" "EQLog.txt" "LTLog.txt")

#   Delimiter to separate sections of report file:
Separator="============================================================"

############################################# fn to check for tar file
#                 param1:  name of file to be checked
isTar() {

   mimeType=`file -b --mime-type $1`
   if [[ $mimeType == "application/x-tar" ]]; then
      return 0
   fi
   if [[ $mimeType == "application/x-gzip" ]]; then
      return 0
   fi
   return 1
}

##################################### fn to extract token from file name
#                 param1: (possibly fully-qualified) name of file
#  Note:  in production use, the first part of the file name will be the
#         student's PID
#
getPID() { 

   fname=$1
   # strip off any leading path info
   fname=${fname##*/}
   # extract first token of file name
   sPID=${fname%%.*}
}
   
############################################################ Validate command line

# Verify number of parameters
   if [[ $# -ne 1 ]]; then
      echo "You must specify the name of your C source file (or -clean)."
      exit 1
   fi
   
# See if user selected the cleaning option
  if [[ $1 == "-clean" ]]; then
     echo "Removing earlier test files..."
     rm -Rf *.txt $buildDir $exeName
     exit 0
  fi

# Verify presence of named file
   sourceFile="$1"
   if [ ! -e $sourceFile ]; then
      echo "The file $sourceFile does not exist."
      exit 2
   fi
   
############################################################ Check for grading package

   if [[ ! -e $gradingTar ]]; then
      echo "$gradingTar is not present"
      exit 3
   fi
   
   isTar $gradingTar
   if [[ $? -ne 0 ]]; then
      echo "$gradingTar does not appear to be a tar file"
      exit 4
   fi

############################################################ Get student's PID
   
   # Extract first token of C file name (student PID when we run this)
   getPID $sourceFile
   # Set name for executable:
   exeName="$sPID-c09"
   echo ">>$sPID<<"
   echo ">>$exeName<<"
   
   # Initiate header for grading log
   headerLog="header.txt"
   echo "Grading:  $1" > $headerLog
   echo -n "Time:     " >> $headerLog
   echo `date` >> $headerLog
   echo >> $headerLog
   
############################################################ Prepare for build
  
   # Create log file:
   echo "Executing gradeC09.sh..." > $buildLog
   echo >> $buildLog
   
   # Create build directory:
   echo "Creating build subdirectory" >> $buildLog
   echo >> $buildLog
   # Create build directory if needed; empty it if it already exists
   if [[ -d $buildDir ]]; then
      rm -Rf ./$buildDir/*
   else
      mkdir $buildDir
   fi
   
   # Copy student's C file to the build directory
   echo "Copying student source file to the build directory:" >> $buildLog
   cp $sourceFile ./$buildDir/$renameC >> $buildLog
   echo >> $buildLog
   
   # Unpack the test source files into the build directory
   echo "Unpacking test code into build directory:" >> $buildLog
   tar xf $gradingTar -C ./$buildDir >> $buildLog

   # Move to build directory
   cd ./$buildDir
   
############################################################ Build the test driver


   #   Build command:
   buildCMD="gcc -o $exeName -std=c11 -Wall -ggdb3 c09driver.c $renameC TestRational.o"
   
   # build the driver; save output in build log
   echo "Compiling test code and submission:" >> ../$buildLog
   echo $buildCMD >> ../$buildLog
   $buildCMD >> ../$buildLog 2>&1
   echo >> ../$buildLog

   # Verify existence of executable
   if [[ ! -e $exeName ]]; then
      echo "Build failed; the file $exeName does not exist" >> ../$buildLog
      echo $Separator >> ../$buildLog
      mv ../$buildLog ../$sPID.txt
      exit 7
   fi
   if [[ ! -x $exeName ]]; then
      echo "Permissions error; the file $exeName is not executable" >> ../$buildLog
      echo $Separator >> ../$buildLog
      mv ../$buildLog ../$sPID.txt
      exit 8
   fi

   echo "Build succeeded..." >> ../$buildLog
   
   # Move executable up to test directory and return there
   echo "Moving the executable $exeName to the test directory." >> ../$buildLog
   mv ./$exeName ..
   cd ..

############################################################ Perform testing
   
   # Set fixed seed for mass testing
   seed="1506303519"
   echo $seed > "seed.txt"

   # Initiate test Log
   echo "Begin testing using seed value $seed" >> $headerLog
   
   # Execute the test code
   echo "Preparing to execute student solution..." >> $testLog
   echo >> $testLog
   timeout -s SIGKILL 60 ./$exeName -repeat >> $testLog 2>&1
   timeoutStatus="$?"
   # echo "timeout said: $timeoutStatus"
   if [[ $timeoutStatus -eq 124 || $timeoutStatus -eq 137 ]]; then
      echo "The test of your solution timed out after 60 seconds." >> $testLog
   elif [[ $timeoutStatus -eq 134 ]]; then
      echo "The test of your solution was killed by a SIGABRT signal." >> $testLog
      echo "Possible reasons include:" >> $testLog
      echo "    - a segfault error" >> $testLog
      echo "    - a serious memory access error" >> $testLog
   fi
   
   # Check for output files:
   for outFile in "${testFiles[@]}"
   do
      if [[ ! -e $outFile ]]; then
         echo "$outFile was not created" >> $testLog
      fi
   done
     
############################################################ File report
# complete summary file

   summaryLog="$sPID.txt"
   
   # write header to summary log
   cat "$headerLog" > $summaryLog
   echo $Separator >> $summaryLog
   
   # write score summary to log
   echo ">>Scores from testing<<" >> $summaryLog
   cat "$scoreFile" >> $summaryLog
   echo $Separator >> $summaryLog
   
   # write test output to summary log
   for outFile in "${testFiles[@]}"
   do
      if [[ -e $outFile ]]; then
         echo $outFile >> $summaryLog
         cat $outFile >> $summaryLog
      else
         echo "$outFile was not found" >> $summaryLog
      fi
      echo >> $summaryLog
      echo $Separator >> $summaryLog
   done
   echo >> $summaryLog
   
   # write build log into summary
   echo "Results from $buildLog" >> $summaryLog
   cat $buildLog >> $summaryLog
   echo >> $summaryLog

exit 0
