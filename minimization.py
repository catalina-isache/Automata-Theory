def adaugare_stare(stare):
    dict = {}
    automat_nou[stare] = {}
    cifra_stare = stare.split(',')[0]
    for litera in limbaj:
        lista = []
        stare_noua=clasa[automat[cifra_stare][litera]]
        lista = sorted(echivalente[stare_noua])
        stare_noua = ""
        for x in lista:
            stare_noua += x+','
        stare_noua=stare_noua[:-1]
        if stare_noua not in automat_nou:
            adaugare_stare(stare_noua)
        dict[litera] = stare_noua
    automat_nou[stare] = dict

def echi(stare1,stare2):
    for litera in limbaj:
        if clasa[automat[stare1][litera]]!=clasa[automat[stare2][litera]]:
            return 0
    return 1

file = open("input.txt")
out = open("output.txt", "w")

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
    automat[stare]=dict

stare_initiala=file.readline().split()[0]
m=int(file.readline())
for x in range(m):
    line=file.readline()
    x,y,litera=line.split()
    automat[x][litera]=y

f=int(file.readline())
finale=[]
echivalente=[[],[]]
clasa={}
for x in file.readline().split():
    finale.append(x)
    echivalente[0].append(x)
    clasa[x]=0

for i in range(1,n+1):
    if str(i) not in echivalente[0]:
        echivalente[1].append(str(i))
        clasa[str(i)]=1

ok=1
nr=1


while(ok):
    ok=0
    lg = len(echivalente)
    clasa_noua = {}
    for i in range(lg):
        echivalente_noi=[[echivalente[i][0]]]
        for stare2 in echivalente[i][1:]:
            pus=0
            j=0
            for lista_noua in echivalente_noi:
                stare1=lista_noua[0]
                if echi(stare1,stare2):
                    echivalente_noi[j].append(stare2)
                    if stare1 in clasa_noua:
                        clasa_noua[stare2]=clasa_noua[stare1]
                    else:
                        clasa_noua[stare2] = clasa[stare1]
                    pus=1
                    break
                j += 1
            if pus==0:
                nr+=1
                clasa_noua[stare2]=nr
                echivalente_noi.append([stare2])

        if len(echivalente_noi)>1:
            ok=1
            echivalente[i]=echivalente_noi[0]
            for lista in echivalente_noi[1:]:
                echivalente.append(lista)
    for x in clasa_noua:
        clasa[x] = clasa_noua[x]

print(echivalente)

automat_nou = {}
for i in range(len(echivalente)):
    stare_noua = ""
    for x in echivalente[i]:
        stare_noua += x+','
    stare_noua=stare_noua[:-1]
    if stare_noua not in automat_nou:
        adaugare_stare(stare_noua)

stari_finale=[]
for stare in automat_nou:
    for cifra_stare in stare:
        if cifra_stare in finale:
            stari_finale.append(stare)
            break

    for litera in automat_nou[stare]:
        print(stare,"->", automat_nou[stare][litera],"cu", litera)

print("Stari finale:")
for x in stari_finale:
    print(x,sep="; ")

