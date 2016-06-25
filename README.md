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
![snapshot-9c2d3ad](https://cloud.githubusercontent.com/assets/4140247/12284558/1a9f278a-b976-11e5-8402-4f50e6f9fbf9.gif)


## How to Install indigoDock
Here is how you run it:  
1. **Download [QtCreator](http://www.qt.io/download-open-source/) and install**  
2. **Clone the indigoDock repository to your local machine** ```mkdir indigoDock; cd indigoDock/; git clone git://github.com/nitramr/indigoDock``` **OR just download the indigoDock [.zip file](https://github.com/nitramr/indigoDock/archive/master.zip)**  
3. **Find and click on the TestLayout.pro which should invoke QtCreator**  
![testlayout pro](https://cloud.githubusercontent.com/assets/15112256/14962010/02eca01c-109d-11e6-8f3a-b7a229af5b92.png)  
4. **Build TestLayout by clicking on the green arrow OR Build > Build Project "TestLayout"**  
![build-indigodock-in-qtcreator](https://cloud.githubusercontent.com/assets/4140247/10866388/01e7e67e-7ffa-11e5-852c-0176e022c647.jpg)  

## Snapshot features:
* the whole dock is dockable on left, right, top or bottom of main window  
* the dock contains a tabbar with sortable tabs (drag and drop sorting)  
* within the container you can add/remove/arrange single panels  
* drag and drop between more than one dock  
* container highlighting by panel hovering  
* application has a theme switcher (dark/light)  
* setting will saved in a settings file  
* auto scroll to active panel by click on link icon  
* panel stack float horizontal or vertical based on dock orientation  


## Issues:
* tabbar icon doesn't update by theme switch (not implemented)  
* empty dock occur resize issue  


## Roadmap v1.0 - Framework
* sorting panels by drag and drop **(done)**  
* automatic tab orientation switch by docking on left site **(done)**  
* function to scroll wanted panel to top by click on related icon or using a shortcut **(done)**  
* panel mode (normal/advanced/collapsed) **(done)**  
* theme support ~~+ icon switch by theme change~~ **(done)**  
* clean up compile time warnings **(done)**  

## Roadmap v1.1 - Multiple Dock support
* drag and drop panels between more than one dock **(done)**  
* load/save workspace **(done)**  
* horizontal panel layout **(done)**  
* floating panel layout  

## Sub Project - Control Element set
* AnglePicker **(done)**  
* Color Preview **(done)**  
* Origin Setter  
