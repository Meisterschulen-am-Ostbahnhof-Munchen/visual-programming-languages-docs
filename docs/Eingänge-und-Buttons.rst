Eingänge und Buttons
===================================

Der Baustein "IX" ist für Eingänge vom Typ BOOL vorgesehen. 
also Eingänge mit 1 Bit Datenbreite, 
oder anders ausgedrückt: ein Schaltsignal das nur 2 Zustände kennt: 0 (Taster losgelassen) oder 1 (Taster gedrückt)

.. image:: https://user-images.githubusercontent.com/69573151/179404465-c9d5080f-fad1-421f-aee4-1f95a8a90990.png

* Eingänge: 

  * INIT Service Initialization
  
    * muss beim Programmstart 1x aufgerufen werden. Wird in der Regel mit dem Ausgang "COLD" des Bausteins "E_RESTART" verbunden. Siehe auch: https://www.eclipse.org/4diac/en_help.php?helppage=html/4diacIDE/use4diacLocally.html und https://www.eclipse.org/4diac/en_help.php?helppage=html/parameters/parameters.html
    
  * REQ Service Request
  
    * wird nicht benötigt. Dieser Eingang kommt von alten Zeiten, als man die Eingänge noch pollen musste. 
    
  * QI Event Input Qualifier
  
    * auf true setzen, damit dieser Baustein funktioniert. 
    
  * PARAMS Service Parameters
  
    * hier wird der Parameter angegeben. Muss als String angegeben werden, also z.B. 'I1'. (die einfachen Hochkommas sind wichtig)
    
* Ausgänge:

  * INITO Initialization Confirm
  
    * wenn INIT aufgerufen wurde, und ausgeführt wurde wird das hier bekanntgegeben. 
    
  * CNF Confirmation of Requested Service
  
    * wird nicht benötigt. Dieser Eingang kommt von alten Zeiten, als man die Eingänge noch pollen musste. 
    
  * IND Indication from Resource
  
    * Dieser Ausgang meldet eine Änderung des Status. Bei einem einfachen Ausgang also sowohl die Änderung 0->1 wie auch 1->0
    
  * QO Event Output Qualifier
  
    * wird "true" wenn QI true ist und INIT aufgerufen wurde. 
    
  * STATUS Service Status
  
    * Hier werden Fehlermeldungen ausgegeben. Wenn kein Fehler vorliegt dann wird OK ausgegeben.
    
  * IN Input data from resource
  
    * Das ist der Zustand des Eingangs, also 0 oder 1 



.. image:: https://user-images.githubusercontent.com/69573151/179405617-a62999a0-8330-4a9c-a0e7-14ed488d7edc.png



.. image:: https://user-images.githubusercontent.com/69573151/179405473-6ca8a44d-6c9b-46b8-b78f-bc9164141fb4.png



Denkbare Werte für PARAMS
----------------------------

Ix
............................

damit sind die Werte I1, I2, I3 gemeint, diese bilden folgende Eingänge ab: 

* I1 => GPIO_NUM_26 
* I2 => GPIO_NUM_32 
* I3 => GPIO_NUM_39

damit ist folgende Applikation machbar: 

ein M5 Stack Atom Lite (https://shop.m5stack.com/products/atom-lite-esp32-development-kit) plus ein Dual Button (https://shop.m5stack.com/products/mini-dual-button-unit) ergeben folgende Zuordung: 

* I1 => der Button "B" (gelbe Drahtfarbe) roter Knopf
* I2 => der Button "A" (weiße Drahtfarbe) blauer Knopf
* I3 => der Button auf dem M5 Atom Lite


AIx
............................

damit sind die Werte AI1, AI2, AI3, AI4, AI5, AI6 gemeint, diese bilden folgende Eingänge ab: 

Nur der Kanal GPIO_NUM_32 also der weiße draht ist in der Lage Analoge Buttons zu verarbeiten. 

Der Schaltplan findet sich hier: https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/feature/ButtonBoards/ButtonBoards/6ButtonTHT

wenn die Eingänge AIx verwendet werden darf der Eingang I2 natürlich nicht gleichzeitig verwendet werden. Die Eingänge I1 und I3 sind davon nicht betroffen. 

es können also 6 Buttons mit einem Draht eingelesen werden. Drücken von 2 Tasten gleichzeitig funktionieren dann natürlich nicht. 



.BUTTON_PRESS_NORMAL
............................

damit ist gemeint dass man an AIx oder Ix einen Suffix anhängt. 
Zum Beispiel AI1.BUTTON_PRESS_NORMAL oder I3.BUTTON_PRESS_NORMAL

.BUTTON_PRESS_NORMAL hat keine andere Funktion, 
somit entspricht I1 = I1.BUTTON_PRESS_NORMAL

in diesem Fall wird am Ausgang IN der Zustand abgegeben, und im Ausgang IND ein Event je Zustandswechsel. 

bei einem Kurzen Tastendruck mit loslassen würde man also 2 Events am Ausgang IND erwarten. 



.BUTTON_PRESS_DOWN
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim Drücken des Buttons gesendet, nicht beim Loslassen. 
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_PRESS_UP
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim Loslassen des Buttons gesendet, nicht beim Drücken. 
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_PRESS_REPEAT
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event bei Mehrfachklicks des Buttons gesendet. 
Wird dieser Parameter beim Baustein IB verwendet, so enthält IN die Anzahl der Clicks. Damit sind interessante Anwendungen möglich. 
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_SINGLE_CLICK
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim Klicken des Buttons gesendet. 
Damit erfolgt kein Event beim Doppelklick.
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_DOUBLE_CLICK
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim Doppelklicken des Buttons gesendet. 
Damit erfolgt kein Event beim Einfach oder Dreifachklick. 
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_LONG_PRESS_START
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim langen drücken des Buttons gesendet. Dieses kommt ein mal pro langem drücken. 
der Ausgang IN bleibt in dieser Variante stets auf 0

.BUTTON_LONG_PRESS_HOLD
............................

wird dieser Suffix angehängt, so wird am Ausgang IND nur ein Event beim langen drücken des Buttons gesendet. Dieses kommt wiederholt solange der Button festgehalten wird. 
der Ausgang IN bleibt in dieser Variante stets auf 0











