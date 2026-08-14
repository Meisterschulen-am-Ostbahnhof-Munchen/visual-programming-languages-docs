# AR_DIVTIME

![AR_DIVTIME](./AR_DIVTIME.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AR_DIVTIME** dient der Division eines Zeitwertes (Typ TIME) durch einen numerischen Wert. Die Eingabe des Divisors erfolgt über einen Adapter, sodass der Baustein flexibel in verschiedenen Kontexten eingesetzt werden kann. Die Ausgabe des Ergebnisses geschieht ebenfalls über einen Adapter. Der Baustein ist gemäß IEC 61131-3 als standard arithmetic function klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ** (Event): Normaler Ausführungsanstoß. Bei einem Ereignis an REQ wird die Division durchgeführt. Der Eingang IN1 muss dabei mit dem REQ-Ereignis verbunden sein (WITH).

### **Ereignis-Ausgänge**

Der Baustein besitzt keine expliziten Ereignisausgänge in der Interface-Liste. Das Ergebnis wird jedoch über den Adapter-Ausgang **OUT** bereitgestellt, welcher ein Ereignis (E1) sendet, sobald die Berechnung abgeschlossen ist (wie aus der internen Verdrahtung ersichtlich).

### **Daten-Eingänge**

- **IN1** (TIME): Zu dividierender Zeitwert (Dividend).

### **Daten-Ausgänge**

Der Baustein hat keine direkten Datenausgänge. Das Divisionsergebnis wird über den Adapter-Ausgang **OUT** als Datenwert (D1) ausgegeben.

### **Adapter**

- **IN2** (Adapter, Typ `adapter::types::unidirectional::AR`): Divisor. Dieser Adapter liefert ein Ereignis (E1) zur Auslösung sowie den Datenwert (D1).
- **OUT** (Adapter, Typ `adapter::types::unidirectional::ATM`): Ausgang für das Divisionsergebnis (TIME). Bereitstellung von Ereignis (E1) und Daten (D1).

## Funktionsweise

Der Funktionsblock AR_DIVTIME kapselt die Funktionalität des internen Bausteins **F_DIVTIME** (Typ `iec61131::arithmetic::F_DIVTIME`).
Bei einem Ereignis am Eingang **REQ** oder alternativ am Adaptereingang **IN2.E1** wird die Division gestartet. Der interne FB dividiert **IN1** (TIME) durch **IN2.D1** (numerischer Wert) und gibt das Ergebnis auf **OUT.D1** aus.
Sobald die Berechnung abgeschlossen ist, wird ein Ereignis an **OUT.E1** gesendet, welches dem nachfolgenden Empfänger signalisiert, dass das Ergebnis gültig ist.

## Technische Besonderheiten

- **Adapter-basierte Schnittstelle:** Statt klassischer Daten-Ein-/Ausgänge werden Adapter verwendet, was eine flexible Verschaltung in komplexen Netzwerken erlaubt. Die Adapter sind als unidirektional definiert und erfordern kompatible Gegenstücke.
- **Standardkonformität:** Der Baustein erfüllt die Anforderungen der IEC 61131-3 (Klassifikation: standard arithmetic function).
- **Interne Kapselung:** Die eigentliche Berechnung erfolgt durch den wiederverwendbaren Baustein F_DIVTIME, sodass AR_DIVTIME als eine Art Wrapper mit adaptergestützter Kommunikation fungiert.
- **Gemischte Schnittstelle:** Anders als vollständig adapterbasierte Bausteine erhält AR_DIVTIME den Dividenden (IN1) als klassischen Dateneingang, nicht über einen Adapter – siehe `ATM_AR_DIVTIME` für die vollständig adapterbasierte Variante.

## Zustandsübersicht

Der Baustein selbst besitzt keine explizite Zustandsmaschine. Die ereignisgesteuerte Abarbeitung erfolgt deterministisch:

- Warten auf Ereignis an **REQ** oder **IN2.E1**
- Ausführen der Division
- Senden des Ergebnisses an **OUT.E1** und **OUT.D1**
- Zurückkehren in den Wartezustand

## Anwendungsszenarien

- Aufteilen eines Zeitwertes in gleiche Abschnitte, z. B. Umrechnung einer Gesamtlaufzeit auf einzelne Zyklen.
- In Steuerungsanwendungen, bei denen ein Zeitparameter dynamisch durch einen variablen Faktor geteilt werden muss.
- Als Bestandteil von Bibliotheken für IEC 61131-3-konforme automatische Steuerung, insbesondere wenn Adapter zur Entkopplung der Signalpfade eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen

- **F_DIVTIME:** Der direkte, adapterfreie Baustein zur Division von TIME durch numerische Werte. Er bietet klassische Ereignis- und Datenschnittstellen. AR_DIVTIME kapselt diesen Baustein und stellt den Divisor über einen Adapter bereit.
- **AR_MULTIME:** Multipliziert statt zu dividieren, ansonsten strukturell identisch (gemischte Schnittstelle: IN1 als Dateneingang, IN2 als Adapter).
- **ATM_AR_DIVTIME:** Die vollständig adapterbasierte Variante – hier ist auch IN1 ein Adapter-Socket (Typ `ATM`) statt eines festen Dateneingangs.

## Fazit

Der Funktionsblock **AR_DIVTIME** ermöglicht die Division eines Zeitwertes durch einen numerischen Faktor über eine adaptergestützte Schnittstelle für den Divisor. Er kombiniert die bewährte IEC 61131-3-Arithmetik mit flexibler Konnektivität und eignet sich besonders für modulare Automatisierungssysteme. Die interne Verwendung des Bausteins F_DIVTIME garantiert eine zuverlässige und effiziente Berechnung.
