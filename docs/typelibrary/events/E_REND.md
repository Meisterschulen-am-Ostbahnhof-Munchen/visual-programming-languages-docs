# E\_REND

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


* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


### **Überblick zu E_REND (Rendezvous) in IEC 61499**

In der IEC 61499, einer Norm für die Modellierung von Funktionsbausteinen in industriellen Automatisierungssystemen, spielen Ereignisse (Events) eine zentrale Rolle bei der Steuerung des Datenflusses und der Synchronisation von Prozessen. Ein spezielles Konzept in diesem Zusammenhang ist das **E_REND** (Rendezvous), das auch als **AND-Verknüpfung von Ereignissen** bezeichnet wird. Es dient dazu, zwei oder mehr Ereignisse zu synchronisieren, bevor eine Aktion ausgelöst wird.

---

### **Was ist E_REND (Rendezvous)?**

Das **E_REND**-Konzept beschreibt einen Mechanismus, bei dem zwei oder mehr Ereignisse gleichzeitig eintreten müssen, bevor ein Ausgangsereignis ausgelöst wird. Es handelt sich um eine **logische UND-Verknüpfung** von Ereignissen, die sicherstellt, dass alle beteiligten Ereignisse synchronisiert sind. Dies ist besonders nützlich in verteilten Steuerungssystemen, bei denen mehrere unabhängige Prozesse aufeinander abgestimmt werden müssen.

---

### **Funktionsweise von E_REND**

1. **Eingangsereignisse:**
   - E_REND hat mindestens zwei Eingangsereignisse (z. B. `EI1` und `EI2`).
   - Diese Ereignisse können von verschiedenen Funktionsbausteinen oder Teilen des Systems stammen.

2. **Synchronisation:**
   - Das Ausgangsereignis (`EO`) wird nur dann ausgelöst, wenn **alle Eingangsereignisse gleichzeitig aktiviert** werden.
   - Wenn nur eines der Ereignisse eintritt, wird das Ausgangsereignis nicht ausgelöst.

3. **Ausgangsereignis:**
   - Das Ausgangsereignis `EO` wird an einen nachgelagerten Funktionsbaustein oder eine Aktion weitergeleitet, sobald alle Eingangsereignisse synchronisiert sind.

---

### **Anwendungsfälle von E_REND**

1. **Synchronisation paralleler Prozesse:**
   - In Produktionsanlagen müssen oft mehrere unabhängige Prozesse synchronisiert werden, bevor ein nächster Schritt eingeleitet wird. Beispiel: Ein Roboter und ein Förderband müssen beide bereit sein, bevor ein Werkstück weiterverarbeitet wird.

2. **Sicherheitskritische Systeme:**
   - In sicherheitskritischen Anwendungen kann E_REND verwendet werden, um sicherzustellen, dass mehrere Bedingungen erfüllt sind, bevor eine Aktion ausgeführt wird. Beispiel: Eine Maschine startet nur, wenn sowohl der Not-Aus-Schalter freigegeben als auch die Schutzabdeckung geschlossen ist.

3. **Verteilte Steuerungssysteme:**
   - In verteilten Systemen, bei denen mehrere Steuerungskomponenten unabhängig voneinander arbeiten, kann E_REND verwendet werden, um deren Ereignisse zu synchronisieren und eine koordinierte Steuerung zu ermöglichen.

---

### **Vorteile von E_REND**

1. **Synchronisation:**
   - E_REND ermöglicht die präzise Synchronisation von Ereignissen, was in komplexen Steuerungssystemen unerlässlich ist.

2. **Flexibilität:**
   - Es kann auf beliebig viele Eingangsereignisse erweitert werden, um komplexe Synchronisationsanforderungen zu erfüllen.

3. **Eindeutigkeit:**
   - Durch die UND-Verknüpfung wird sichergestellt, dass das Ausgangsereignis nur dann ausgelöst wird, wenn alle Bedingungen erfüllt sind.

4. **Einfache Implementierung:**
   - In der IEC 61499 kann E_REND einfach als Teil eines Funktionsbausteins modelliert werden, ohne zusätzliche Programmierung.

---

### **Beispiel in IEC 61499**

Angenommen, ein System besteht aus zwei Sensoren (`Sensor1` und `Sensor2`), die beide ein Ereignis auslösen, wenn sie aktiviert werden. Ein E_REND-Baustein synchronisiert diese Ereignisse und löst ein Ausgangsereignis aus, wenn beide Sensoren gleichzeitig aktiviert sind.

- **Eingangsereignisse:**
  - `EI1` (von `Sensor1`)
  - `EI2` (von `Sensor2`)

- **Ausgangsereignis:**
  - `EO` (wird nur ausgelöst, wenn sowohl `EI1` als auch `EI2` aktiviert sind)

---

### **Fazit**

Das **E_REND (Rendezvous)**-Konzept in der IEC 61499 ist ein leistungsstarkes Werkzeug zur Synchronisation von Ereignissen in industriellen Automatisierungssystemen. Es ermöglicht die präzise Steuerung von Prozessen, indem es sicherstellt, dass mehrere Ereignisse gleichzeitig eintreten müssen, bevor eine Aktion ausgeführt wird. Dies ist besonders in komplexen, verteilten Systemen von großer Bedeutung, bei denen die Koordination und Synchronisation von Prozessen entscheidend für die Effizienz und Sicherheit ist. Durch seine Einfachheit und Flexibilität ist E_REND ein unverzichtbares Element in der Welt der industriellen Automatisierung.
