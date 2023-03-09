# automatul accepta un cuvant daca se goleste stiva
# limbajul din exemplu este {a^i b^i c^j d^j  ∣i, j ≥ 1}
# graful este retinut ca o lista de dictionare
# fiecare stare are dictionarul ei in care literele limbajului sunt cheile,
# iar fiecarei chei ii corespunde o lista de tranzitii posibile din starea
# respectiva, cu cheia respectiva

def functie(stare, cuvant,stiva):
    if len(cuvant)==0 and len(stiva)==0:
        return 1
    else:
        if len(cuvant):
            litera=cuvant[-1]
            cuvant_nou=cuvant[0:-1]
        else:
            litera='e'
            cuvant_nou=""
        for tranzitie in graf[stare][litera]:
            if tranzitie[1]==stiva[0]:
                stiva_noua=stiva[1:]
                if tranzitie[2]!='e':
                    stiva_noua=tranzitie[2]+stiva_noua
                if functie(tranzitie[0],cuvant_nou,stiva_noua)==1:
                    return 1
            else:
                if tranzitie[1]=='e':
                    stiva_noua=tranzitie[2]+stiva_noua
                    if functie(tranzitie[0], cuvant_nou,stiva_noua)==1:
                        return 1
    return 0



file = open("input.txt")
#formatul inputului este
# nr stari n 1,2,..n
#limbaj
#stare initiala
#simbol baza stiva
# nr tranzitii
# tranzitii: stare_curenta next_state litera_din_limbaj,top_stiva/push_stiva
#nr_cuvinte
#cuvinte de verificat


n=int(file.readline())  #nr stari, starile vor fi de la 1 la n
limbaj=file.readline().split()     #literele limbajului

stare_initiala=int(file.readline().split()[0])
simbol_stiva=file.readline().split()[0]     #simbolul de baza al stivei
graf=[]
for i in range(n+1):
    graf.append({})


m=int(file.readline())     #tranzitiile automatului: stare_curenta next_state litera_din_limbaj,top_stiva/push_stiva
for i in range(m):
    line=file.readline()
    x,y,tranzitie=line.split()
    x=int(x)
    y=int(y)
    simbol,schimbare=tranzitie.split(',')
    top_stiva, inlocuire=schimbare.split('/')
    lista=[y,top_stiva,inlocuire]
    if simbol not in graf[x]:
        lista = [lista]
        graf[x][simbol]=lista
    else:
        graf[x][simbol].append(lista)


nr_cuv=int(file.readline())
for i in range(nr_cuv):
    cuvant=file.readline().strip()
    cuvant=cuvant[-1::-1]
    stiva=simbol_stiva
    if functie(stare_initiala,cuvant,stiva)==1:
        print("Acceptat")
    else:
        print("Neacceptat")


