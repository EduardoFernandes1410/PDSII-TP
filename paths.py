import os
root_folder = "./20_newsgroups"
folders = os.listdir(root_folder)
f = open("input.txt", "w")
for folder in folders:
    arquivos = os.listdir(os.path.join(root_folder, folder))
    for arquivo in arquivos:
        print(arquivo)
        f.write((os.path.join(root_folder,folder, arquivo) + "\n"))

