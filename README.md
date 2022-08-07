
# Project is no longer maintained
I found a well maintained framework that match all needs. See here: https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System
Check latest status here to see it in action: [Scribus-IndigoUI-Mockup](https://github.com/nitramr/Scribus-IndigoUI-Mockup)


[![Join the chat at https://gitter.im/nitramr/indigoDock](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/nitramr/indigoDock?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
# indigoDock 
Experimental Qt Docking extension written for Scribus1.5>=  

## Update ##

I decided to stop developing of IndigoDock as single project as seen on https://github.com/nitramr/indigoDock. My code doesn't fit well in current Scribus code base.

Now, I'm full focused on integration of IndigoDock in Scribus and all necessary optimizations and upgrades. In short words: I'm developing a special version of IndigoDock which fits perfectly in Scribus code base directly in the Scribus code. Later I will put back the improvements and useful upgrades to the original separate project that others can use it for their application.

Working Scribus Version which uses IndigoDock you can find here: https://github.com/nitramr/scribus-indigo

### Work in progress
Currently I'm on restoring the panel and dock settings for workspace saving. And I'm on fixing some UX issues. But basic integration was successfully and the dock is usable. ;)

Thank you guys for waiting so long time for real results.

greets,
@nitramr


## Proposal Mockups
![scribus_ui_fullhd](https://cloud.githubusercontent.com/assets/4140247/10866901/27f00cba-8014-11e5-91f8-8894712e08ce.png)

![scribus_ui_panels](https://cloud.githubusercontent.com/assets/4140247/10866907/6fe10a9c-8014-11e5-9d46-8fd4ec9ecc33.png)

![scribus_ui_panels_detailed](https://cloud.githubusercontent.com/assets/4140247/10866918/5d8ae97a-8015-11e5-85ad-a27eeaaad4ce.png)

### Relevant Links 
* Read the [indigoDock Proposal](https://goo.gl/T4gFd5) (on google slides)  
* Discussions occcuring in the [Scribus UI/UX sub-forums](http://forums.scribus.net/index.php/topic,1617.0.html).  

## Current Development Snapshot
![indigodock showreel](https://cloud.githubusercontent.com/assets/15112256/16357320/3490f50c-3af3-11e6-8ca1-8ae7f204bb1f.gif)


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
* workspace can saved in a settings file  
* auto scroll to active panel by click on link icon  
* panel stack float horizontal or vertical based on dock orientation  
* drop of a floating panel outside of a dock creates a new dock  


## Issues:
* tabbar icon doesn't update by theme switch (not implemented)  


## Roadmap v1.0 - Framework
* sorting panels by drag and drop **(done)**  
* automatic tab orientation switch by docking on left site **(done)**  
* function to scroll wanted panel to top by click on related icon or using a shortcut **(done)**  
* panel mode (normal/advanced/~~collapsed~~) **(done)**  
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
