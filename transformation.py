def adaugare_stare(stare):
    dict = {}
    automat_nou[stare] = {}
    for litera in limbaj:
        lista = []
        for cifra_stare in stare.split(','):
             lista.extend(automat[cifra_stare][litera])
        lista = sorted(set(lista))
        stare_noua = ""
        for x in lista:
            stare_noua += x+','
        stare_noua=stare_noua[:-1]
        if stare_noua not in automat_nou:
            adaugare_stare(stare_noua)
        dict[litera] = stare_noua
    automat_nou[stare] = dict


file = open("input.txt")

# nr stari n 1,2,..n
#limbaj
#stare initiala
# nr muchii
# x y litera
# nr stari finale
# starile finale
automat={}
n=int(file.readline())
limbaj=file.readline().split()
for i in range(1,n+1):
    stare=str(i)
    dict = {}
    for litera in limbaj:
        lista=[]
        dict[litera]=lista
    automat[stare]=dict

stare_initiala=file.readline().split()[0]
m=int(file.readline())
for x in range(m):
    line=file.readline()
    x,y,litera=line.split()
    automat[x][litera].append(y)

f=int(file.readline())
finale=[]
for x in file.readline().split():
    finale.append(x)

automat_nou={}
print(automat)
stari_finale=[]
adaugare_stare(stare_initiala)
for stare in automat_nou:
    for cifra_stare in stare:
        if cifra_stare in finale:
            stari_finale.append(stare)

    for litera in automat_nou[stare]:
        print(stare,"->", automat_nou[stare][litera],"cu", litera)

print("Stari finale:")
for x in stari_finale:
    print(x,sep=" ")

