#! /usr/bin/python

import string,sys,os,shutil, glob
from subprocess import *

def median(numbers):
   "Return the median of the list of numbers."
   # Sort the list and take the middle element.
   n = len(numbers)
   copy = numbers[:] # So that "numbers" keeps its original order
   copy.sort()
   if n & 1:         # There is an odd number of elements
      return copy[n // 2]
   else:
      return (copy[n // 2 - 1] + copy[n // 2]) / 2

def make():
#	os.system("make fyp")
	os.system("mkdir -p build/Release")
	shutil.copyfile("./FYP","./build/Release/FYP")	
	shutil.copyfile("./input-ecb.cpp","./build/Release/input-ecb.cpp")
	shutil.copyfile("./input-ctr.cpp","./build/Release/input-ctr.cpp")
	os.system("chmod +x ./build/Release/FYP")
	
def generate(args):
	print args
	os.chdir("build/Release")
	p = Popen("./FYP "+args,shell=True, stdout=PIPE)
	result = p.communicate()[0]
	print result
	os.chdir("../..")
	
def tidy():
	os.remove(os.getcwd()+"/build/Release/FYP")
	os.remove(os.getcwd()+"/build/Release/input-ecb.cpp")
	os.remove(os.getcwd()+"/build/Release/input-ctr.cpp")

def copyfiles():
	shutil.copyfile("../../../aes.cpp","./aes.cpp")
	shutil.copyfile("../../../aes.h","./aes.h")
	shutil.copyfile("../../../aes256.c","./aes256.c")
	shutil.copyfile("../../../aes256.h","./aes256.h")
	shutil.copyfile("../../../utils.cpp","./utils.cpp")
	shutil.copyfile("../../../utils.h","./utils.h")
	shutil.copyfile("../../../input-ecb.h","./input-ecb.h")
	shutil.copyfile("../../../input-ecb.cpp","./input-ecb.cpp")		
	shutil.copyfile("../../../input-ctr.h","./input-ctr.h")
	shutil.copyfile("../../../testOutput.h","./testOutput.h")
	shutil.copyfile("../../../testOutput.cpp","./testOutput.cpp")
	shutil.copyfile("../../../Quad.h","./Quad.h")
	shutil.copyfile("../../../H. G. Wells - War of the Worlds.txt","./H. G. Wells - War of the Worlds.txt")

def info(v):
     return '%s = %r %s' % (v, v, type(v))

def test():
	shutil.copyfile("./input-ecb.cpp","./build/Release/input-ecb.cpp")
	shutil.copyfile("./input-ctr.cpp","./build/Release/input-ctr.cpp")	
	
	z = filter(lambda x: x.find("output")>=0,(os.listdir("./build/Release")))
	os.chdir("build/Release")
	
	results = dict()
	
	for i in z:
		os.makedirs("test-"+i)
		os.chdir("test-"+i)
		shutil.copyfile("../"+i,"./"+i)
		copyfiles()
		os.system("g++-4.2 `papiex-config --cflags` -fopenmp -m64 *.cpp *.c  -O3 `papiex-config --libs` -Wno-deprecated")
		
		l = []
					
		while ((len(glob.glob(os.path.join(".","*papiex*")))) < 5):
			p1 = Popen("papiex -e PAPI_VEC_INS -e PAPI_L1_DCM -e PAPI_TOT_CYC ./a.out",shell=True, stdout=PIPE, stderr=PIPE)
			p2 = Popen(["grep","PAPI_TOT_CYC"],stdin=p1.stderr, stdout=PIPE)
			p3 = Popen(["grep","%"],stdin=p2.stdout, stdout=PIPE)
			p4 = Popen(["awk","{printf $3}"],stdin=p3.stdout, stdout=PIPE)
			val = p4.communicate()[0].strip();
			if (len(val) > 0 and int(val) > 0):
				l.append(int(val))
				print i + "...\t" + val + " cycles"
#			else:
#				print i + " invalid \t" + val + " cycles"
		
		if (len(l)>0):
			results[i] = median(l);
			print i + ": median \t\t" + str(results[i]) + " cycles"
		os.chdir("..")
		
	invertedResults = dict(map(lambda item: (item[1],item[0]),results.items()))
	print "\nWinner is: " + invertedResults[min(invertedResults.keys())]
		
	os.chdir("../..")

def main():
	
	make()
	
	print 'Encryption Code Generator activated.\n'
	print 'Warning: Large numbers of temporary files will be created. Please stand back for your own safety.\n'
	print 'Thank you.\n'
	
	if len(sys.argv) == 1:
		generate("+ss +ui +local +unroll +leave +omp")
	else:
		generate(' '.join(sys.argv[1:]))
	
	#tidy()
	
	test()
	
main()
	
#for i in sys.argv[1:]:
