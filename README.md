# indigoDock
Experimental Qt Docking extension written for Scribus1.5>= 

## Proposal Mockups
![scribus_ui_fullhd](https://cloud.githubusercontent.com/assets/4140247/10866901/27f00cba-8014-11e5-91f8-8894712e08ce.png)

![scribus_ui_panels](https://cloud.githubusercontent.com/assets/4140247/10866907/6fe10a9c-8014-11e5-9d46-8fd4ec9ecc33.png)

![scribus_ui_panels_detailed](https://cloud.githubusercontent.com/assets/4140247/10866918/5d8ae97a-8015-11e5-85ad-a27eeaaad4ce.png)

For more details read the [indigoDock google slides proposal](https://goo.gl/T4gFd5). Discussions occuring @ UI/UX sub-forum in the [Scribus Forums](http://forums.scribus.net/index.php/topic,1617.0.html).  

## Install
Here is how you run it:  
1. **Download [QtCreator](http://www.qt.io/download-open-source/) and install**  
2. **Clone the indigoDock repository to your local machine**  
3. **Find and click on the TestLayout.pro which should invoke QtCreator**  
![testlayout pro](https://cloud.githubusercontent.com/assets/4140247/10866360/21cef028-7ff9-11e5-8c4c-e0e86c682868.png)  
4. **Build TestLayout by clicking on the green arrow OR Build > Build Project "TestLayout"**  
![build-indigodock-in-qtcreator](https://cloud.githubusercontent.com/assets/4140247/10866388/01e7e67e-7ffa-11e5-852c-0176e022c647.jpg)  

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
