# Programación III: Proyecto Final (2024-1)

## Integrantes
* Nombre y Apellidos
* Nombre y Apellidos
* Nombre y Apellidos
* Nombre y Apellidos

El siguiente texto debe ser eliminar en su repositorio.

## Plataforma de Streaming
El objetivo del proyecto final es implementar una plataforma de *streaming*. Un programa que administre la búsqueda y visualización de la sinopsis de películas. Para ello se debe implementar las siguientes operaciones:

* El programa debe leer la base de datos en forma **.csv**. La base de datos puede ser descargada desde el siguiente [link](https://drive.google.com/file/d/1iusSIbmXJW_OUBm6X7Ik593rgCGPCPza/view?usp=sharing).
* El programa debe cargar este archivo en una **estructura de datos** que permita una rápida búsqueda de una película.
* Para buscar una película se debe utilizar una palabra o frase. También se debe poder buscar películas por el **Tag**: cult, horror, etc.
* Al buscar películas deben de aparecer la cinco más **importantes** y una opción para visualizar las siguientes cinco coincidencias.
* Al seleccionar una película, se debe visualizar la sinopsis y las opciones **Like** y **Ver más tarde** .
* Al iniciar el programa la plataforma debería mostrar las películas que fueron añadidas en **Ver más tarde**. Además, se debe visualizar las películas similares a las que el usuario les dio **Like** (implemente su propio algoritmo).

## Requisitos
* Grupos de cuatro personas como máximo y de tres como mínimo. No se aceptarán grupos de dos o una persona.
* Subir el programa a un repositorio en Github. Aquí debe de estar toda la documentación sobre el proyecto.
* Grabar su presentación y colocar el link en su repositorio. El video debe tener un máximo de 15 minutos. Aquel grupo que sobrepase el tiempo tendrá una penalización en su nota.
* Cumplir con la rúbrica del proyecto.

## Convenciones de escritura
* Utilizamos snake_case para las variables.
* Utilizamos cammelCase para las funciones y metodos de clases.
* NUNCA hacemos uso de PascalCase.

## Descripcion de directorios

* src -> Source directory containing our main program components.
  * src\app -> Directory contains the main class components management, as well as entities.
    * src\app\Movie -> Contains everything regarding movies and its associated components (included sub-entities)
    * src\app\SearchEngine -> Contains everything related to search modules, technologies and scripts.
    * src\app\TriePrefix -> Contains anything to the tree search model. Includes search modules, technologies and scripts.
  * src\beta_modules -> Any script that stands as suggestion or experimentation goes here.
  * src\tools -> All classes and scripts dedicated to being complementary for the project go here.

## Conceptos Importantes
Para la busqueda de las peliculas, se utilizo un arbol de prefijos, Trie. 
![image](https://github.com/user-attachments/assets/88db7d43-4819-4c89-b4d5-7ced8d95972d)

Donde despues de formar las palabras, hay un nodo adicional donde se guarda la direccion a las peliculas a la cual la palabra esta relacionado. 
