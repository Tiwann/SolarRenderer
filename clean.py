import os
import platform


if platform.system() == "Linux":
	success = os.system("./Vendor/Premake5/premake5 clean")
elif platform.system() == "Windows":
	success = os.system("Vendor\\Premake5\\premake5.exe clean")
else:
	print("Cannot clean on this platform! Are you running on Linux or Windows ?")

if success != 0:
	print("An Error occurred")
quit()