### Q\_NumericValue

![](https://user-images.githubusercontent.com/113907471/204326982-47eea33a-9b9c-4107-8f96-97c85a945fbc.png)

Normativen Referenz: 

Dieser Funktionsbaustein bezieht sich auf den Abschnitt ISO 11783-6 F.22 Change Numeric Value command

ACHTUNG: dieser Befehl kann so oft aufgerufen werden wie vom Anwendungsprogrammierer gewünscht, jedoch kann ein zu häufiges Aufrufen den ISOBUS stark überlasten, weshalb dieser Baustein mit Bedacht eingesetzt werden sollte. 

Aufgabe dieses Bausteins ist es eine der folgenden Objekte die auf einem VT dargestellt werden zu aktualisieren: 

*   Boolean input field: 1 byte for TRUE/FALSE  

![](https://user-images.githubusercontent.com/69573151/227978868-275bbdb4-4a27-4325-b79a-e06a92a48244.png)

*   Number input field: 4 bytes for integer input

![](https://user-images.githubusercontent.com/69573151/227978954-813af40a-0d6b-4add-92ee-4adb9e6a1df9.png)

*   List input field: 1 byte for list index 

![](https://user-images.githubusercontent.com/69573151/227979018-91510384-180d-450b-a34e-c8a8ec7c12ed.png)

*   List output field: 1 byte for list index
    *   (wie list Input field, jedoch in VT3 nicht vorhanden) 
*   Number output field: 4 bytes for integer output
*   Meter: 2 bytes for integer value
*   Linear bar graph: 2 bytes for integer value
*   Arched bar graph: 2 bytes for integer value
*   Number variable: 4 bytes for integer value
*   Die Number Variable kann nicht direkt auf dem Display angezeigt werden, kann aber mit allen bisher genannen Objekten verknüpft werden; Vorteil: auch mehrfache Verknüpungen Möglich. 
*   Object pointer: 2 bytes for Object ID
*   Sinnvoll um andere Objekte an Stelle des Pointers ein& und auszublenden.   
     

BEISPIEL

Zähler mit Rücksetzung

![](https://user-images.githubusercontent.com/113907471/204327132-b1a058c2-7ccb-4374-af56-d309ae8798a5.png)
