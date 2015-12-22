[![Join the chat at https://gitter.im/nitramr/indigoDock](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/nitramr/indigoDock?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
# indigoDock 
Experimental Qt Docking extension written for Scribus1.5>=  

## Proposal Mockups
![scribus_ui_fullhd](https://cloud.githubusercontent.com/assets/4140247/10866901/27f00cba-8014-11e5-91f8-8894712e08ce.png)

![scribus_ui_panels](https://cloud.githubusercontent.com/assets/4140247/10866907/6fe10a9c-8014-11e5-9d46-8fd4ec9ecc33.png)

![scribus_ui_panels_detailed](https://cloud.githubusercontent.com/assets/4140247/10866918/5d8ae97a-8015-11e5-85ad-a27eeaaad4ce.png)

### Relevant Links 
* Read the [indigoDock Proposal](https://goo.gl/T4gFd5) (on google slides)  
* Discussions occcuring in the [Scribus UI/UX sub-forums](http://forums.scribus.net/index.php/topic,1617.0.html).  

## Current Development Snapshot
![indigodock tester_002](https://cloud.githubusercontent.com/assets/15112256/11666883/e7e91a14-9dee-11e5-9c43-4b0a2c84af70.png)


## How to Install indigoDock
Here is how you run it:  
1. **Download [QtCreator](http://www.qt.io/download-open-source/) and install**  
2. **Clone the indigoDock repository to your local machine** ```mkdir indigoDock; cd indigoDock/; git clone git://github.com/nitramr/indigoDock``` **OR just download the indigoDock [.zip file](https://github.com/nitramr/indigoDock/archive/master.zip)**  
3. **Find and click on the TestLayout.pro which should invoke QtCreator**  
![testlayout pro](https://cloud.githubusercontent.com/assets/4140247/10866360/21cef028-7ff9-11e5-8c4c-e0e86c682868.png)  
4. **Click "Projects" (1), choose "Debug" (2), uncheck "Shadow build" (3), choose "Release" (2), uncheck "Shadow build" (3)**  
![indigodock_settings](https://cloud.githubusercontent.com/assets/15112256/11942773/1b5a8e9c-a839-11e5-8a50-a897ec7a7236.png)  
5. **Build TestLayout by clicking on the green arrow OR Build > Build Project "TestLayout"**  

![build-indigodock-in-qtcreator](https://cloud.githubusercontent.com/assets/4140247/10866388/01e7e67e-7ffa-11e5-852c-0176e022c647.jpg)  

## Snapshot features:
* the whole dock is dockable on left or right side of main window  
* the dock contains a tabbar with sortable tabs (drag and drop sorting)  
* within the container you can add/remove/arrange single panels (more than one)  
* container highlighting by panel hovering  
* application has a theme switcher (dark/light)  
* setting will saved in a settings file  


## Issues:
* panel sorting by drag and drop doesn't work well in any case  
* tabbar icon doesn't update by theme switch (not implemented)  
* panel resizing for undocked panels doesn't work well  


## Roadmap v1.0 - Framework
* sorting panels by drag and drop **(almost done)**  
* automatic tab orientation switch by docking on left site **(done)**  
* function to scroll wanted panel to top by click on related icon or using a shortcut  
* panel mode (normal/advanced/collapsed) **(done)**  
* theme support + icon switch by theme change **(almost done)**  
* clean up compile time warnings  

## Roadmap v1.1 - Control Element set
* AnglePicker **(started)**  
* Grouped Buttons  
* Color Preview **(almost done)**  
* Origin Setter  
* Icon Label Container  
