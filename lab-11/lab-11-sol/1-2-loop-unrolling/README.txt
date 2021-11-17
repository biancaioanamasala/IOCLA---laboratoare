Exercitiul 1.
    1. Se fac mai putine jump-uri, mai putine pipeline stall-uri
    2. Timpul de executie al unei instructiuni nu este acelasi mereu + depinde si ce face sistemul de operare.

Exercitiul 2.
    1. Compilatorul observa ca variabila sum nu este folosita nicaieri in afara for-ului asa ca elimina forul
    2. Acum variabila este folosita de catre printf, asa ca nu va mai fi eliminat for-ul la optimizare
    3. Nu se mai fac branch-uri in plus, sunt mai putin instructiuni executate.
    4. -fpeel-loops care se activeaza la O3 stie sa inlocuiasca for-ul, in situatii in care numarul de iteratii este mic,
       astfel incat sa nu se faca niciun jump.
    5. Nu este nicio diferenta. Nu se aplica nicio optimizare.
