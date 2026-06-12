# AR_MULTIME


![AR_MULTIME](./AR_MULTIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_MULTIME** dient der Multiplikation eines Zeitwertes (Typ TIME) mit einem numerischen Wert. Die Eingabe des numerischen Faktors erfolgt über einen Adapter, sodass der Baustein flexibel in verschiedenen Kontexten eingesetzt werden kann. Die Ausgabe des Ergebnisses geschieht ebenfalls über einen Adapter. Der Baustein ist gemäß IEC 61131-3 als standard arithmetic function klassifiziert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** (Event): Normaler Ausführungsanstoß. Bei einem Ereignis an REQ wird die Multiplikation durchgeführt. Der Eingang IN1 muss dabei mit dem REQ-Ereignis verbunden sein (WITH).

### **Ereignis-Ausgänge**
Der Baustein besitzt keine expliziten Ereignisausgänge in der Interface-Liste. Das Ergebnis wird jedoch über den Adapter-Ausgang **OUT** bereitgestellt, welcher ein Ereignis (E1) sendet, sobald die Berechnung abgeschlossen ist (wie aus der internen Verdrahtung ersichtlich).

### **Daten-Eingänge**
- **IN1** (TIME): Erster Funktionsinput – der zu multiplizierende Zeitwert.

### **Daten-Ausgänge**
Der Baustein hat keine direkten Datenausgänge. Das Multiplikationsergebnis wird über den Adapter-Ausgang **OUT** als Datenwert (D1) ausgegeben.

### **Adapter**
- **IN2** (Adapter, Typ `adapter::types::unidirectional::AR`): Zweiter Funktionsinput – der numerische Multiplikator. Dieser Adapter liefert ein Ereignis (E1) zur Auslösung sowie den Datenwert (D1).
- **OUT** (Adapter, Typ `adapter::types::unidirectional::ATM`): Ausgang für das multiplizierte Ergebnis (TIME). Bereitstellung von Ereignis (E1) und Daten (D1).

## Funktionsweise
Der Funktionsblock AR_MULTIME kapselt die Funktionalität des internen Bausteins **F_MULTIME** (Typ `iec61131::arithmetic::F_MULTIME`).  
Bei einem Ereignis am Eingang **REQ** oder alternativ am Adaptereingang **IN2.E1** wird die Multiplikation gestartet. Der interne FB multipliziert **IN1** (TIME) mit **IN2.D1** (numerischer Wert) und gibt das Ergebnis auf **OUT.D1** aus.  
Sobald die Berechnung abgeschlossen ist, wird ein Ereignis an **OUT.E1** gesendet, welches dem nachfolgenden Empfänger signalisiert, dass das Ergebnis gültig ist.

## Technische Besonderheiten
- **Adapter-basierte Schnittstelle:** Statt klassischer Daten-Ein-/Ausgänge werden Adapter verwendet, was eine flexible Verschaltung in komplexen Netzwerken erlaubt. Die Adapter sind als unidirektional definiert und erfordern kompatible Gegenstücke.
- **Standardkonformität:** Der Baustein erfüllt die Anforderungen der IEC 61131-3 (Klassifikation: standard arithmetic function).
- **Interne Kapselung:** Die eigentliche Berechnung erfolgt durch den wiederverwendbaren Baustein F_MULTIME, sodass AR_MULTIME als eine Art Wrapper mit adaptergestützter Kommunikation fungiert.

## Zustandsübersicht
Der Baustein selbst besitzt keine explizite Zustandsmaschine. Die ereignisgesteuerte Abarbeitung erfolgt deterministisch:
- Warten auf Ereignis an **REQ** oder **IN2.E1**
- Ausführen der Multiplikation
- Senden des Ergebnisses an **OUT.E1** und **OUT.D1**
- Zurückkehren in den Wartezustand

## Anwendungsszenarien
- Skalierung von Zeitwerten durch einen konstanten oder variablen Faktor, z. B. Umrechnung von Sekunden in Millisekunden oder Verlängerung von Verzögerungszeiten.
- In Steuerungsanwendungen, bei denen Zeitparameter dynamisch angepasst werden müssen, etwa in Verbindung mit PID-Reglern oder Zeitplanungen.
- Als Bestandteil von Bibliotheken für IEC 61131-3-konforme automatische Steuerung, insbesondere wenn Adapter zur Entkopplung der Signalpfade eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen
- **F_MULTIME:** Der direkte, adapterfreie Baustein zur Multiplikation von TIME mit numerischen Werten. Er bietet klassische Ereignis- und Datenschnittstellen. AR_MULTIME hingegen kapselt diesen Baustein und stellt die Schnittstellen über Adapter bereit, was die Wiederverwendbarkeit in adapterbasierten Architekturen erhöht.
- **AR_MUL:** Ein allgemeiner Multiplikationsbaustein mit Adaptern, der für beliebige numerische Typen ausgelegt sein könnte. AR_MULTIME ist speziell auf TIME-Werte spezialisiert.

## Fazit
Der Funktionsblock **AR_MULTIME** ermöglicht die Multiplikation eines Zeitwertes mit einem numerischen Faktor über eine moderne, adaptergestützte Schnittstelle. Er kombiniert die bewährte IEC 61131-3-Arithmetik mit flexibler Konnektivität und eignet sich besonders für modulare Automatisierungssysteme, die auf standardisierte Adapter setzen. Die interne Verwendung des Bausteins F_MULTIME garantiert eine zuverlässige und effiziente Berechnung.