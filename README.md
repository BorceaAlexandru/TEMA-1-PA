README TEMA 1 PA:

Structura:
	1.main.c 
		-Aici deschid fisierele, iar ulterior citesc numarul de echipe din fisierul de input. Creez o structura de tip team in care urmeaza sa stochez datele pentru fiecare echipa. vectorTask este un vector in care bag datele din c.in pentru a vedea la ce task ma aflu, iar apoi, in functie de valoarea fiecarui indice apelez functiile pentru fiecare task. (task1, task2 samd). In final inchid fisierele
	2.librariamea.h
		-Aici am urmatoarele structuri:
			-struct Team
				-name = numele echipei
				-punctajTotal = punctajul total al echipei
				-next = pointer catre urmatoarea echipa din lista

			-struct Player
				-firstName = prenume
				-secondName = nume
				-points = punctajul jucatorului

			-struct Coada_Nod -> structura definita pentru a reprezenta un nod dintr o coada
				-struct Team* team1 = pointer catre prima echipa
				-struct Team* team2 = pointer catre a 2 a echipa
				-struct Coada_Nod* next = pointer catre urmatorul nod din coada

			-struct Coada -> structura definita pentru a gestiona coada de meciuri
				-struct Coada_Nod* fata = pointer catre primul nod din coada
				-struct Coada_Nod* spate = pointer catre ultimul nod din coada

			-struct Stiva_Nod -> structura definita pentru a reprezenta un nod dintr o stiva
				-struct Team* team = pointer catre echipa stocata in acest nod
				-struct Stiva_Nod* next = pointer catre urmatorul nod din stiva

			-struct Stiva -> structura pentru gestionarea stivei
				-struct Stiva_Nod* varf -> pointer catre nodul din varf al stivei

			-struct Arbore_Nod -> structura pentru BST
				-struct Team* team -> pointer catre echipa din nod
				-struct Arbore_Nod* dreapta -> pointer catre subarborele drept
				-struct Arbore_Nod* stanga -> pointer catre subarborele stang
		-Dupa structuri apelez functiile enqueue, dequeue etc., dar si functiile task
	3.librariamea.c

	FUNCTII:

		-Functia "stergCaractere" : se foloseste pentru a elimina spatiile de la sfarsitul unui sir de caractere
			-Prima data obtin indicele ultimului spatiu din sir. Apoi, folosind un while, aflu care e ultimul caracter diferit de spatiu si in final "inchid" sirul la pozitia corecta
		
		-Functia "citireSir" : se foloseste pentru a citi cate un cuvant 
			-Verific daca pointerul catre fisier este NULL sau nu. Dupa declar un buffer in care voi stoca temporar cuvantul din fisier, apoi aloc memorie pentru a stoca cuvantul citit + 1 pentru '\0'. Urmeaza sa copiez buffer in cuv si sa returnez cuv, adica cuvantul din fisier

		-Functia "citireNumeEchipa" : se foloseste pentru a citi o linie intreaga din fisier
			-Verific daca pointerul catre fisier este NULL sau nu. Dupa declar un buffer in care voi stoca temporar linia din fisier, apoi folosesc fgetc(fisier) pentru a elimina spatiul ramas dupa citirea numarului de jucatori. Citesc linia, iar apoi apelez "stergCaractere(buffer)" pentru a elimina spatiile de la final. Aloc memorie pentru nume + 1 ('\0'), copiez buffer in namesi returnez name
	
		-Functia "creeazaEchipa" : creez echipa si o adauga la inceputul listei
			-Aloc memorie pt o noua structura, care primeste nume si punctajTotal. Dupa, pointerul next este setat la head (noua echipa devine capul listei), iar head vechi va deveni urmatorul element din lista. In final returnez ultima echipa
	
		-Functia "eliminaEchipa" : elimina echipe din lista de echipele cu cel mai mic punctaj astfel incat numarul de echipe sa fie putere a lui 2
			-while-ul verifica daca numarEchipe este putere a lui 2. Curent incepe de la capul listei, prev urmareste nodul anterior, minPrev retine nodul anterior celui cu punctaj minim si minTeam retine echipa cu punctaj minim. Se trece prin lista, iar daca se gaseste o echipa cu punctajul total mai mic decat minTeam, se actualizeaza minTeam si minPrev. Daca minPrev este NULL, inseamna ca echipa cu punctaj minim este chiar prima din lista, deci capul este actualizat. Eliberez memoria ocupata de nume si de structura, iar numarEchipe e decrementat si procesul se repeta oana cand numarEchipe devine o putere a lui 2

		-Functia "createQueue"	: folosita pentru a crea o coada noua
			-Aloc memorie pentru o structura Coada. fata si spate sunt initializate cu NULL pentru ca (,) coada este initial vida, iar apoi returnez pointer catre coada

		-Functia "enqueue" : folosita pentru a adauga doua echipe in coada
			-Incep prin a verifica daca e goala coada. Apoi aloc memorie pt un nou nod, iar informatiile despre cele 2 echipe sunt atribuite campurilor team1 si team2 ale acelui nod. Verific iar daca e goala coada pentru a vedea cum actualizez pointerii "fata" si "spate". Daca e goala coada pointerii sunt actualizati la noul nod si se termina functia. Daca nu e goala, noul nod este legat la sfarsitul cozii, iar pointerul "spate" este actualizat la noul nod

		-Functia "dequeue" : elimina primul element din coada
			-Verific daca e goala coada, daca e nu am nimic de eliminat. Salvez pointerul catre primul nod al cozii in "nod", apoi actualizez coada->fata pentru a indica urmatorul nod din coada. Daca dupa eliminare pointerul de inceput devine NULL inseamna ca s a golit coada, iar pointerul de sfarsit devine NULL. Eliberez memoria pentru nodul eliminat din coada.

		-Functia "coadaGoala" : se foloseste pentru a verifica daca e goala coada

		-Functia "createStack" : o folosesc pentru a crea o stiva noua
			-Alocare de memorie pentru o structura de tip Stiva. Pointerul catre varf este initializat cu NULL, adica indica faptul ca stiva este initial vida, apoi returneaza pointerul catre stiva nou creata

		Functia "push" : adauga un nou element in varful stivei
			-Aloc memorie pentru un nou nod, apoi echipa este atribuita campului team al noului nod si dupa fac legatura noului nod la varful stivei

		Functia "pop" : elimin un element din varful stivei
			-Verific daca stiva e goala (daca varf==NULL). Apoi salvez pointerul catre varf in newNode si actualizez pointerul de varf al stivei pentru a indica urmatorul nod din stiva

		Functia "stivaGoala" : verifica daca e goala stiva

		Functia "Nod_Nou" : folosita pentru a crea un nod nou pentru un arbore
			-Aloc memorie pentru un nou nod. Noul nod va contine referinta catre echipa asociata. Initializez stanga si dreapta cu NULL pt ca nodul nu are subarbori la momentul crearii, iar apoi returnez nodul

		Functia "insert" : folosita pentru a insera un nou nod intr un arbore
			-Verific daca arborele e gol. Se verifica valoarea punctajului echipei pe care vreau sa o adaug cu valoarea punctajului nodului curent, iar in functie de asta adaug echipa in stanga sau in dreapta nodului curent. Daca key->punctaj < nod->punctaj se va duce in stanga, daca nu, in dreapta si daca sunt egale comparam numele echipelor. Returnez nodul curent modificat

		Functia "printare" : printare pentru task4
			-Daca arborele nu este gol am realizat o apelare recursiva a functiei pentru subarborele drept. Apoi se afiseaza valoarea arborelui curent, iar in final o apelare recurisva pentru valorile din stanga. 

	FUNCTII TASK:

		Functia "task1" : rezolva taskul 1
			-Se foloseste de "citireNumeEchipa" pentru a citi fiecare nume de echipa, iar de "citireSir" pentru a citi prenumele si numele jucatorilor. Se foloseste de "creeazaEchipa" pentru a crea o echipa. In final if-ul se executa doar daca sunt la task1, daca am trecut nu.
		
		Functia "task2" : rezolva taskul 2
			-Se foloseste de "eliminaEchipa" si apoi scrie in fisierul de output numele echipei ramase

		Functia "task3" : rezolva taskul 3
			-In primul rand creez o coada de meciuri, o stiva de castigatori si o stiva de pierzatori. Echipele sunt bagate in coada meciuri, consecutiv, doua cate doua. Primul while se executa pana cand coada de meciuri este goala. Al 2 lea while este pentru meciuri, unde echipele sunt extrase din coada. Se afiseaza numele echipelor, se determina castigatorul si se adauga in stive corespunzator. Dupa meci se afiseaza castigatorul. Castigatorii sunt bagati iar intr o coada de meciuri.

		Functia "task4" : rezolva taskul 4
			-Initializez un arbore binar de cautare (BST) cu NULL. Parcurg lista top8 (primele 8 echipe de la task3) si inserez fiecare echipa in BST folosind "insert". Folosesc functia "printare" pentru a afisa echipele din BST in ordine crescatoare a punctajelor in fisierul de output.
		

	
	
																				
				
