# AUI_AX_SEL_AUI

binary selection


![AUI_AX_SEL_AUI](./AUI_AX_SEL_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_AX_SEL_AUI** realisiert eine binäre Auswahl zwischen zwei Eingangswerten vom Typ **AUI**. Die Entscheidung, welcher Eingang an den Ausgang weitergeleitet wird, erfolgt über einen dritten Adapter vom Typ **AX**, der als Selektor dient. Der Baustein kapselt die in IEC 61131-3 definierte Funktion **F_SEL** und stellt sie als adapterbasierte Komponente bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **G.E1** (über Adapter G): Triggert die Auswahlverarbeitung, sobald ein Ereignis am Selektor-Adapter anliegt.

### **Ereignis-Ausgänge**
- **OUT.E1** (über Adapter OUT): Wird ausgelöst, nachdem der ausgewählte Wert am Ausgang anliegt.

### **Daten-Eingänge**
- **G.D1** (über Adapter G): Der selektierende Wert (z. B. BOOL oder numerisch), der bestimmt, ob **IN0** oder **IN1** ausgewählt wird.
- **IN0.D1** (über Adapter IN0): Erster Eingangswert vom Typ **AUI**.
- **IN1.D1** (über Adapter IN1): Zweiter Eingangswert vom Typ **AUI**.

### **Daten-Ausgänge**
- **OUT.D1** (über Adapter OUT): Der ausgewählte Wert (Typ **AUI**), entsprechend der Selektionslogik.

### **Adapter**
- **G** (Socket, Typ `adapter::types::unidirectional::AX`): Liefert das Selektionssignal.
- **IN0** (Socket, Typ `adapter::types::unidirectional::AUI`): Erster Datenkanal.
- **IN1** (Socket, Typ `adapter::types::unidirectional::AUI`): Zweiter Datenkanal.
- **OUT** (Plug, Typ `adapter::types::unidirectional::AUI`): Ergebniskanal.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert über die Adapter-Schnittstellen. Sobald ein Ereignis am Selektor **G.E1** eintrifft, wird der interne Funktionsblock **F_SEL** aktiviert. **F_SEL** prüft den Wert **G.D1**:
- Ist **G.D1** = `FALSE` (oder 0), wird der Wert von **IN0.D1** an den Ausgang **OUT.D1** weitergegeben.
- Ist **G.D1** = `TRUE` (oder ungleich 0), wird **IN1.D1** ausgewählt.

Nach Abschluss der Selektion signalisiert **F_SEL.CNF** das Ereignis **OUT.E1**, um den Verbraucher über den neuen gültigen Ausgangswert zu informieren.

## Technische Besonderheiten
- Der Baustein ist als **Composite-FB** realisiert – das Verhalten ergibt sich aus der inneren Verschaltung eines standardisierten **F_SEL**-Blocks (IEC 61131-3).
- Die Daten werden über Adapter vom Typ **AUI** und **AX** übertragen. Diese Adaptertypen sind als unidirektionale Kanäle definiert, deren interne Datenstruktur nicht näher spezifiziert ist (z. B. Integer, Real, oder benutzerdefinierte Structs).
- Die Auswahl erfolgt rein kombinatorisch, jedoch erst nach einem auslösenden Ereignis am Selektor. Ein reiner Datenwechsel ohne Ereignis führt nicht zu einer Aktualisierung des Ausgangs.

## Zustandsübersicht
Da es sich um einen Composite-FB ohne eigenen Zustandsautomaten handelt, existieren keine expliziten Zustände. Die Logik ist rein ereignisgesteuert:
1. **Warte auf Ereignis** – solange kein **G.E1** eintrifft, bleibt der Ausgang unverändert.
2. **Auswahl durchführen** – nach **G.E1** wird der entsprechende Eingang ausgewählt und der Ausgang gesetzt.
3. **Ausgang signalisieren** – **OUT.E1** wird nach erfolgreicher Auswahl generiert.

## Anwendungsszenarien
- **Umschaltung zwischen zwei Messwerten** (z. B. Temperatur von Sensor A oder B) basierend auf einem Steuersignal.
- **Betriebsartumschaltung** in der Automatisierungstechnik, bei der je nach Modus unterschiedliche Stellgrößen aktiviert werden.
- **Redundante Signalquellen** – falls der primäre Kanal (IN0) ausfällt, kann über den Selektor auf den sekundären Kanal (IN1) umgeschaltet werden.

## Vergleich mit ähnlichen Bausteinen
- **MUX (Multiplexer)**: Ein Multiplexer wählt aus mehr als zwei Eingängen aus; **AUI_AX_SEL_AUI** ist auf zwei Eingänge spezialisiert und verwendet Adapter statt einzelner Signale.
- **F_SEL (Standard IEC 61131)**: Der innere Baustein bietet identische Funktionalität, jedoch ohne Adapter-Kapselung. Der vorliegende FB erweitert ihn um eine adapterbasierte Schnittstelle, was die Wiederverwendung in adapterorientierten Architekturen erleichtert.
- **SEL (Selection)**: Ähnliche Logik, aber meist als reiner Funktionsbaustein ohne Ereignissteuerung definiert. Hier wird die Auswahl explizit durch ein Ereignis ausgelöst.

## Fazit
**AUI_AX_SEL_AUI** ist ein adapterbasierter Composite-FB für die einfache binäre Auswahl zwischen zwei AUI-Datenströmen. Durch die Verwendung von `F_SEL` im Inneren wird eine robuste und standardkonforme Selektionslogik gewährleistet. Der Baustein eignet sich besonders für modulare Automatisierungslösungen, bei denen Daten über unidirektionale Adapter ausgetauscht werden.