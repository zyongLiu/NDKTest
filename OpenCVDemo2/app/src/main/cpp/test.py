import os

def bianLi(rootDir):
	for root,dirs,files in os.walk(rootDir):
		for file in files:
			print(file.replace('.a',''))
		for dir in dirs:
			bianLi(dir)

rootDir = "F:\\WorkPlace\\NDKTest\\OpenCVDemo2\\app\\src\\main\\cpp\\opencv\\3rdparty\\libs\\arm64-v8a"
bianLi(rootDir)
