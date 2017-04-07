# Main README
Project developers : Mélanie Bochu, Léo Dupouy, 
                     Hédi Ghédiri, Gabriel Hernando, 
		     Jean-Marie Oillarburu, Raphaël Tapia, Johan Vitrat

L'archive PFA_free_bike_project.tar est le rendu du projet.

##Directory arborescence

This project is separated in different modules which are in different subdirectories. Each subdirectories contains their own README file giving some infos.

The **sgbd** we developed is in the *sgbd* directory.

The **download scripts** for bikes data are located in the *download_bike* directory.

The **interface** classes using Qt to make an user interface are located in the *interface* directory.

The **CityDB** class which deals with the import and the saving of the city databse is located in the *import* directory.

The **controllers** classes which articulate each different modules the ones with the others are located in the *controller* directory.

The **OSM** classes dealing with the download, the saving and the display of the OpenStreetMap maps are located in the *osm* directory.

The **HeatMap** class permitting us to display a heat map graph with tulip is located in the *visualisations* directory.

##Project compilation
The stuff permitting us to ompile the project is located in the directory interface/PFA, 
there is a **PFA.pro** file which is giving the needed parameters to execute 
a ***qmake*** command which will generate a Makefile.

##Library dependencies
This project needs different libraries wrappy, tulip, doxygen, python.

##Project licence
    Free_bike_project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Free_bike_project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
<<<<<<< HEAD
    along with free_bike_project.  If not, see <http://www.gnu.org/licenses/>.


=======
    along with free_bike_project.  If not, see <http://www.gnu.org/licenses/>.
>>>>>>> 5b79295569501812756e3a37ba7a570720010d35
