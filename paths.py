import os
import glob
root_folder = "./dataset"
f = open("input.txt", "w")
folders = os.listdir(root_folder)
root_files = glob.glob(os.path.join(root_folder, "*"))
for file in root_files:
	if( not os.path.isdir(file) ):
		print(file)
		f.write("."+os.path.join(file) + "\n")

for folder in folders:
	if(os.path.isdir(os.path.join(root_folder, folder))):
		arquivos = glob.glob(os.path.join(root_folder, folder, "*"))
		for arquivo in arquivos:
			print(arquivo)
			f.write("."+ arquivo + "\n")

