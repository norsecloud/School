#!/usr/bin/python

import os
import sys
import re
import subprocess
import concurrent.futures


# returns the input string but green if stdout is a tty, otherwise does nothing
def green(s):
    return "\033[32m" + str(s) + "\033[m" if sys.stdout.isatty() else str(s)


# runs the given executable with the filename as an argument, and checks it against the expected_output
# will auto-fail after timeout_seconds seconds so the process isn't running forever
#
# returns (True, filename)                 if the program's output matched the expected_output
# returns (False, filename, actual_output) if not
def test(executable, filename, expected_output, timeout_seconds=10):
    # open the given process as if you typed "executable filename" into the shell
    # shell=True is needed to prevent a bug in python <3.8 where proc.kill() does not actually kill the process
    # stderr is merged with stdout so we can also capture error output
    with subprocess.Popen(" ".join([executable, filename]), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True) as proc:
        try:
            # get stdout from the process until EOF or timeout_seconds pass
            s = (proc.communicate(timeout=timeout_seconds)[0]).decode()
        except subprocess.CalledProcessError as e:
            # if the process didn't return 0, get the output from the exception
            s = e.output
        except subprocess.TimeoutExpired as e:
            # the process is not actually killed if the timeout expires. this kills it
            proc.kill()
            if e.output is not None:
                s = e.output.decode()
            else:
                s = ""
            s += "\n\nTimed out after " + str(timeout_seconds) + " seconds"
        # kill the process one more time. probably not needed but i just want to be sure
        proc.kill()

    # if our output ended up being bytes and not a string, decode it
    if type(s) == bytes:
        s = s.decode().strip()
    else:
        s = str(s).strip()

    if s != expected_output:
        return False, filename, s
    else:
        return True, filename


# the directory of test.py
# __file__ is a string that equals the current file, in this case test.py
base = os.path.dirname(os.path.abspath( __file__ ))
# the sorted directories within test.py, excluding those that start with '.' or '__'
dirs = list(sorted(x for x in os.listdir(base) if os.path.isdir(os.path.join(base, x)) and not (x.startswith('.') or x.startswith('__'))))


def print_help():
    print("" + str(sys.argv[0]) + " v 1.4")
    print("Runs test cases on your shit code")
    print()
    print("USAGE:")
    print("\t" + str(sys.argv[0]) + " [options] [path of p-script] " + str(dirs) + "")
    print("\tThe script should be able to be executed on the command-line as './p-script filename.txt'")
    print()
    print("FLAGS:")
    print("\t-h, --help             Prints this screen")
    print("\t-s, --single-threaded  Run only one case at a time. Use this if your code writes to files.")


# the maximum number of working threads. we want to set this to (number of cores * 3) or 5 if we have a single cpu
max_threads = max(5, os.cpu_count() * 3)
# the path to the p-script
p_script = None
# the test case folder
test_cases = None


# process command-line arguments
if len(sys.argv) == 1:
    print_help()
    sys.exit(0)


for arg in sys.argv[1:]:
    # if this is a flag argument
    if arg.startswith("-"):
        # -h or --help
        if arg[1:] == "h" or arg[1:] == "-help":
            print_help()
            exit(0)
        # -s or --single-threaded
        elif arg[1:] == "s" or arg[1:] == "-single-threaded":
            max_threads = 1
        else:
            print_help()
            print()
            print("Unrecognized argument '" + str(arg) + "'")
            sys.exit(1)
    else:
        # this is a positional argument. set p_script/test_cases accordingly
        if p_script is None:
            p_script = arg
        elif test_cases is None:
            test_cases = arg
        else:
            print_help()
            print()
            print("Got an extra argument '" + str(arg) + "'.")
            sys.exit(1)


if p_script is None:
    print_help()
    print()
    print("Expected a p-script, didn't get one.")
    sys.exit(1)

if test_cases is None:
    print_help()
    print()
    print("Expected a test suite within " + str(dirs) + ", didn't get one.")
    sys.exit(1)

if not os.path.exists(p_script):
    print("The given p-script at '" + str(p_script) + "' does not exist.")
    sys.exit(1)

if not os.path.isfile(p_script):
    print("The given p-script at '" + str(p_script) + "' is a directory.")
    sys.exit(1)

if not os.access(p_script, os.X_OK):
    print("The given p-script at '" + str(p_script) + "' is not executable. Run 'chmod a+x " + str(p_script) + "' and try again.")
    sys.exit(1)

if not os.path.isdir(base):
    print("base dir " + str(base) + " does not exist. fatal fuckin error")
    sys.exit(1)

basedir = "" + str(base) + "/" + str(test_cases) + ""
if not os.path.isdir(basedir):
    print("Invalid set of cases '" + str(test_cases) + "'. Must be one of " + str(dirs) + ".")
    sys.exit(1)

if not os.path.isdir("" + str(basedir) + "/accept"):
    print("The given set of cases is missing '" + str(basedir) + "/accept'.")
    sys.exit(1)

if not os.path.isdir("" + str(basedir) + "/reject"):
    print("The given set of cases is missing '" + str(basedir) + "/reject'.")
    sys.exit(1)


# the threads themselves
threads = []
# an array of (filename, output) containing files that should have printed ACCEPT, but printed something else
failed_accept = []
# an array of (filename, output) containing files that should have printed REJECT, but printed something else
failed_reject = []
# the total number of cases. we increment this for each thread we make
len_total = 0
# the absolute path of the p_script
abspath = os.path.abspath(p_script)


# the executor executes threads as you submit() them
# all threads are automatically joined at the end of the with block
# max_workers will be 1 if --single-threaded is specified
with concurrent.futures.ThreadPoolExecutor(max_workers=max_threads) as executor:
    accept_jobs = []
    reject_jobs = []

    # for each file in the accept folder of the given test_cases suite
    for test_case in os.listdir("" + str(basedir) + "/accept"):
        len_total += 1
        # runs a thread equivalent to the below:
        #
        # test(abspath, "" + str(basedir) + "/accept/" + str(test_case) + "", "ACCEPT")
        #
        # the above function tests the p_script with the given case and wants it to output ACCEPT.
        # executor.submit() returns a "future" that will contain our return value when the job completes, so we store that in accept_jobs
        accept_jobs.append(executor.submit(
            test,
            abspath,
            "" + str(basedir) + "/accept/" + str(test_case) + "",
            "ACCEPT",
        ))

    for test_case in os.listdir("" + str(basedir) + "/reject"):
        len_total += 1
        # test(abspath, "" + str(basedir) + "/reject/" + str(test_case) + "", "REJECT")
        reject_jobs.append(executor.submit(
            test,
            abspath,
            "" + str(basedir) + "/reject/" + str(test_case) + "",
            "REJECT",
        ))

    # loop through as the accept jobs finish
    for aj in concurrent.futures.as_completed(accept_jobs):
        # get the return value
        # if the test() function threw, this will also throw
        res = aj.result()
        # if the output didn't match, add it to our failed list
        if not res[0]:
            failed_accept.append((res[1], res[2]))

    for rj in concurrent.futures.as_completed(reject_jobs):
        res = rj.result()
        if not res[0]:
            failed_reject.append((res[1], res[2]))


for fname, output in failed_accept:
    print("Failed case '" + str(fname) + "'")
    print(">>>")
    print(green(open(fname, "r").read()))
    print(">>>")
    print("Expected:")
    print(">>>")
    print(green("ACCEPT"))
    print(">>>")
    print("Actual:")
    print(">>>")
    print(green(output))
    print(">>>")
    print()

for fname, output in failed_reject:
    print("Failed case '" + str(fname) + "'")
    print(">>>")
    print(green(open(fname, "r").read()))
    print(">>>")
    print("Expected:")
    print(">>>")
    print(green("REJECT"))
    print(">>>")
    print("Actual")
    print(">>>")
    print(green(output))
    print(">>>")
    print()

print("Failed " + str(green(str(len(failed_accept) + len(failed_reject)))) + " out of " + str(green(str(len_total))) + " cases")
exit(len(failed_accept) + len(failed_reject))

