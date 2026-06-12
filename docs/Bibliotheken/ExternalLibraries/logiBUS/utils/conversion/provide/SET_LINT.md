# SET_LINT


![SET_LINT](./SET_LINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **SET_LINT** dient dazu, einen Wert vom Typ `LINT` (64‑Bit‑Ganzzahl) aus einem Dateneingang in eine als InOut‑Parameter deklarierte Variable zu schreiben. Er wird typischerweise verwendet, um explizit den Wert einer Variablen zu setzen, die außerhalb des Bausteins definiert ist. Der Baustein folgt der Norm IEC 61499‑1 und stellt einen einfachen, ereignisgesteuerten Schreibzugriff bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Beschreibung                          | Mit Variablen |
|------|-------|---------------------------------------|---------------|
| REQ  | Event | Auslösung des Schreibvorgangs         | IN, OUT       |

### **Ereignis-Ausgänge**
| Name | Typ   | Beschreibung                          | Mit Variablen |
|------|-------|---------------------------------------|---------------|
| CNF  | Event | Bestätigung nach erfolgreichem Schreiben | OUT           |

### **Daten-Eingänge**
| Name | Typ  | Initialwert | Beschreibung                |
|------|------|-------------|-----------------------------|
| IN   | LINT | 0           | Der zu schreibende Wert     |

### **Daten-Ausgänge**
Der Baustein besitzt keine klassischen Datenausgänge, sondern einen **InOut‑Parameter** `OUT`, der gleichzeitig als Ein‑ und Ausgang fungiert. Dieser Parameter ist der Zielspeicherort für den Wert von `IN`.

### **Adapter**
Keine.

## Funktionsweise
Das Verhalten des Bausteins ist auf einen einzelnen Schritt reduziert:
1. Ein Ereignis am Eingang **REQ** löst die interne Verarbeitung aus.
2. Der Algorithmus führt die Zuweisung `OUT := IN` aus. Dadurch wird der Wert des Dateneingangs `IN` in die InOut‑Variable `OUT` kopiert.
3. Nach Abschluss der Zuweisung wird das Ereignis **CNF** gesendet, um die erfolgreiche Ausführung zu signalisieren.

Die InOut‑Variable `OUT` muss in der Applikation an einen Speicherort (z. B. eine globale oder gerätespezifische Variable) gebunden sein. Der Baustein überschreibt den dort gespeicherten Wert mit dem Wert von `IN`.

## Technische Besonderheiten
- Der Baustein verwendet einen **InOut‑Parameter** anstelle eines separaten Datenausgangs. Dies ermöglicht das direkte Schreiben auf eine externe Variable, ohne dass eine zusätzliche Verschaltung über einen Datenausgang erforderlich ist.
- Der Datentyp `LINT` (64‑Bit signed integer) ist plattformabhängig; die Implementierung setzt voraus, dass das Zielsystem diesen Typ unterstützt.
- Es gibt keine Fehlerbehandlung oder Bereichsprüfung – die Zuweisung erfolgt immer, sobald `REQ` ausgelöst wird.
- Der Baustein ist ein **SimpleFB** mit nur einem ECR‑Zustand, daher ist das Verhalten deterministisch und schnell.

## Zustandsübersicht
Der Baustein besitzt lediglich einen Zustand `REQ`. Nach Ausführung des Algorithmus wechselt er automatisch zurück in den Startzustand (implizit). Eine Zustandsmaschine im klassischen Sinne existiert nicht – der Baustein ist stateless. Nach jedem `REQ`‑Ereignis wird genau ein Schreibvorgang durchgeführt.

## Anwendungsszenarien
- **Initialisierung von LINT‑Variablen**: Setzen einer globalen Konfigurationsvariablen auf einen definierten Startwert.
- **Steuerungs‑/Regelungsparameter ändern**: Dynamisches Überschreiben eines Parameters (z. B. Sollwert oder Grenzwert) durch einen übergeordneten Baustein.
- **Test‑ und Debug‑Schnittstellen**: Ermöglicht das manuelle Setzen von Variablen zur Laufzeit über eine HMI oder ein Skript.
- **Nachrichtenkopf‑/Payload‑Setzen**: In der Kommunikation kann `IN` den Wert einer Nachricht enthalten, der in einen Puffer (`OUT`) geschrieben wird.

## Vergleich mit ähnlichen Bausteinen
- **SET_DINT / SET_INT**: Analoge Bausteine für `DINT` (32‑Bit) bzw. `INT` (16‑Bit). Der Unterschied liegt ausschließlich im Datentyp.
- **MOVE**: Ein allgemeinerer Baustein zum Kopieren beliebiger Werte, oft ebenfalls mit InOut‑Parametern. `SET_LINT` ist spezialisiert auf `LINT` und bietet keine weiteren Daten‑ oder Ereigniseingänge.
- **WRITE_LINT (hypothetisch)**: Ein Baustein, der eine Adresse explizit über einen Pointer schreibt. `SET_LINT` arbeitet ohne Adressierung und erwartet eine direkt verbundene Variable.

## Fazit
`SET_LINT` ist ein minimalistischer Funktionsbaustein, der eine einzige Aufgabe zuverlässig erfüllt: das Zuweisen eines `LINT`‑Werts an eine InOut‑Variable. Aufgrund seiner Einfachheit eignet er sich besonders für leistungskritische oder überschaubare Steuerungsaufgaben, bei denen keine komplexe Logik erforderlich ist. Der Verzicht auf Fehlerbehandlung macht ihn transparent und vorhersagbar, erfordert aber eine korrekte Anbindung der InOut‑Variable durch den Anwender.