### XwMcuLibrary ###
-------------------------------------------------------------------------------- 
This is the start of my simple Arduino (possible one day more MCUs) Library.    
It's not meant to be a feature-complete-class library.    
It has what I need, and i will add more only as/if i need it.    

Example: the XwMcuEsp8266 class works only as a Client.   
It has no server functionality because i don't need it.    

### Why? ###
--------------------------------------------------------------------------------    
I don't like having many different libraries, manage all the different versions     
and possible waste program space with similar code on many of them.     

I prefer one library with all that i usually need (within reason).     
It's easier to manage versions and reuse code.      

The compiler/linker will take care to include only what you use, so not      
much wasted program space.      

As for the code, it's not the most optimized you will find.     
In fact, i will admit that is not a priority to me.      
If you have to "scrape" every last byte in order to fit the code into     
the MCU... maybe you need a different MCU.       

Of corse this is "just your opinion man!"       

### Classes ###
--------------------------------------------------------------------------------    
Now, a word about something that may confuse people:      
I don't usually use the object constructor      
Why? Because i may want to declare one global object but change its settings      
at run time. So, i initialize objects with a "Begin" method and not with      
with the constructor.     

* XwMcuSwitch
* XwMcuRotaryEncoder
* XwMcuATdevice
* XwMcuEsp8266
* XwMcuM590
* XwMcuRunningAverage
* XwMcuPzem004T

## In case you are feeling generous  
[![PayPal donate button](https://www.paypalobjects.com/webstatic/en_US/btn/btn_donate_pp_142x27.png)](https://www.paypal.me/maxsnts)