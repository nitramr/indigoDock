# indigoDock
Qt Docking extension written for Scribus1.5  
Proposal that describes this project [indigoDock](https://goo.gl/T4gFd5) in more detail.  
Discussions occuring in UI/UX sub-forum in the [Scribus Forums](http://forums.scribus.net/index.php/topic,1617.0.html)  

## Install
Here is how you run it:  
1. Download [QtCreator](http://www.qt.io/download-open-source/) and install  
2. Clone the indigoDock repository to your local machine  
3. Find and click on the TestLayout.pro which should invoke QtCreator  
4. Build TestLayout by clicking on Build > Build Project "TestLayout"  

## Features:
* the whole dock is dockable on left or right side of main window  
* the dock contains a tabbar with sortable tabs  
* within the single tabs you can add/remove/arrange single panels (more than one) 

## Issues:
* redocking of panels in another tab is a little bit tricky (but I'm on the fix)  

## ToDo's
* fixing of redocking in other tabs
* automatic tab orientation switch by docking on left site
* automatic tab creation by drag a panel on it
* styling of the features

## Code base:
* DockWidget is a normal QDockWidget  
* IndigoTabWidget is a custom QTabWidget  
* IndigoDockWidget is a custom QMainWindow (tab body)  
* IndigoPanel is a custom QDockWidget  
