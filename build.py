import os
import platform

success = 0
if platform.system() == "Linux":
	print("Building Makefile...")
	success = os.system("./Vendor/Premake5/premake5 gmake2 --file=SolarRenderer.lua --subsystem=console")
elif platform.system() == "Windows":
	print("Building Visual Studio 2022 Solution...")
	success = os.system("Vendor\\Premake5\\premake5.exe vs2022 --file=SolarRenderer.lua --windowed")
else:
	print("Cannot build on this platform! Are you running on Linux or Windows ?")

if success != 0:
	print("An Error occurred")
quit()