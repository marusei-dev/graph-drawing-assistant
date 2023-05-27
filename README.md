 # Graph Drawing Assistant
 
## Overview
Graph Drawing Assistant (GDA) is a desktop GUI application that enables a user to digitally draw, analyse, and save graphs.

## Chapter 1. Introduction and Problem Statement.
As said above, GDA is designed to assist the user in drawing, analysing, and saving (and thus sharing) graphs. It is written entirely in C++ with the use of the Qt framework in the Qt Creator environment. The idea of writing an application of such kind originated because of the observation of the author how much tedious work is involved in solving a range of problems in graph theory, such as finding the vertex/edge chromatic number or the minimum size of edges composing perfect matching, to name just a few.

## Chapter 2. Solution Design and Implementation
### Few Remarks on Qt
The Qt framework was chosen as the tool to add the graphical user interface to the application. It comes with readymade widgets and on top of that allows creation of custom elements. This made drawing vertices and edges possible. The unique feature of Qt of signal-slot communication is used extensively throughout the programme in realisation of buttons, actions, mouse clicks processing among other things.
### General Structure
The window space is divided into four parts - the top menu bar, two dock widgets, and the so-called canvas.
#### Top Menu Bar
The top menu bar contains two items - File and Edit. The File menu further contains two actions - Save Graph and Load Graph. The names of the actions speak for themselves - they save/load the graph drawn on the canvas to the file stored in the main directory of the application called “LastGraph.txt”. Thus, in this implementation only one graph can be stored/restored.
#### Dock Widgets
##### Toolbar Dock Widget
The toolbar dock widget contains buttons and, in general, tools that are used to create/alter the graph. As of now there are two buttons - Add Node and Add Undirected Edge. 
###### “Add Node” Button
The Add Node button enables the user to add a vertex/node (the notation is mixed throughout the application) to the graph. For this button, the one-key shortcut “V” can be used. After pressing the button or using the shortcut, the user must click onto the canvas area, and a window prompting the user to enter the name of the vertex will appear. “Enter” must be pressed in order to confirm the input and add the vertex.
###### “Add Undirected Edge” Button
The Add Undirected Edge button allows the user to add an undirected edge to the graph. For this button, the one-key shortcut “E” can be used. After the button is pressed or the shortcut is used, a window will appear, where the user can specify from which vertex to which vertex they want to draw the edge. The two dropdown menus are designed in such a way that it is impossible to choose the same vertex in both of them.
##### Properties Dock Widget
The properties dock widget contains information about the graph. As of now, it shows the number of vertices and edges currently on the canvas.
#### Canvas
Canvas is the main working area of the programme.

## Chapter 3. External Solutions and Deviations.
Apart from the usage of Qt, no other external libraries or APIs were used in the creation of GDA.

## Chapter 4. Testing and Verification.
No unit-testing or similar technique was used for testing this project. The application was checked numerous times for whether it serves the intended purpose.

## Chapter 5. Results, Discussion, and Future Enhancements.
The Graph Drawing Assistant application in its current form is, to put it mildly, far from being complete. The minimal requirements of the final project are met in their entirety, and if that had been the initial goal, it would have been already achieved. However, observing how it looks even with so few features, I am still proud of the work that has been done and undertake to continue work on the project after the semester and its final exams end. I have many ideas how this application could be improved, since so much can be done with the graphs! Speaking concretely, in the future I desire to add more tools to the toolbar, such as a “Add a Directed Edge” button. The top bar menu could also have a tab called “Algorithms”, from where the user will be able to run algorithms of the shortest paths, Dijkstra’s and so on and so forth.

## Chapter 6. Conclusion and References.
In conclusion, I feel I must mention that I used the help from ChatGPT when how something works in Qt was unclear to me. The loadLastGraph slot in the CanvasWidget class is also written with the help of the AI entirely, because I did not know how to properly parse the text which represents a graph.
