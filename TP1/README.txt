Exercice 34 : 

Si le programme se termine alors que le buffer d’écriture n’était pas plein, 
les données restantes dans le buffer ne seront pas écrites dans le fichier.
Il faut donc vérifier si tous les buffers sont vidés après l'exécution de la fonction fflush.

Au mieux, on pourrait lister tous les fichiers utilisé dans notre programmes
Quand on onvre un fichier on l'ajoute dans la liste 
En parcourait la liste, dans mini exit , on les flacherait chacun .