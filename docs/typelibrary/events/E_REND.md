### E\_REND

Rendezvous (AND) of two events

![](https://user-images.githubusercontent.com/113907528/204900982-61a35320-e656-4b42-b0cf-43d8db93ebf0.png)

*   Input
    *   EI1 first event to wait for 
    *   EI2 second event to wait for 
    *   R reset the FB to inital state (i.e., wait again for both events)
*   Output
    *   EO triggered when both EI1 and EI2 occured at least Eingabe/Input:

Eingang/Input

\-EI1 erstes Ereignis, auf das gewartet werden soll

\-EI2 zweites Ereignis, auf das gewartet werden soll

\-R (wie ein reset-Knopf)  
setzt den FB auf den Ausgangszustand zurück (d.h. wartet erneut auf beide Ereignisse)

Ausgabe/Output:

\-EO wird nur ausgelöst,  
wenn sowohl EI1 als auch EI2 mindestens einmal aufgetreten sind!
