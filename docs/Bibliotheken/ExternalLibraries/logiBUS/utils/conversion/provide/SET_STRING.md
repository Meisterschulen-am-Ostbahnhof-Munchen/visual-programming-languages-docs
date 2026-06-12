# SET_STRING


![SET_STRING](./SET_STRING.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `SET_STRING` dient dazu, einen über den Dateneingang `IN` bereitgestellten Zeichenkettenwert (STRING) in eine In‑Out‑Variable `OUT` zu schreiben. Die Ausführung erfolgt gesteuert durch ein Ereignis am Eingang `REQ`. Nach dem Schreiben wird ein Bestätigungsereignis am Ausgang `CNF` gesendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                     | Mit Variablen |
|------|-------|-------------------------------|---------------|
| REQ  | Event | Normaler Ausführungsauftrag   | IN, OUT       |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                      | Mit Variablen |
|------|-------|--------------------------------|---------------|
| CNF  | Event | Bestätigung der Ausführung     | OUT           |

### **Daten-Eingänge**

| Name | Typ    | Kommentar            |
|------|--------|----------------------|
| IN   | STRING | Der zu schreibende Wert |

### **Daten-Ausgänge**

| Name | Typ    | Kommentar                       |
|------|--------|---------------------------------|
| OUT  | STRING | Zielvariable (In‑Out) – nach der Ausführung identisch mit IN |

> **Hinweis:** `OUT` ist als In‑Out‑Variable deklariert. Sie dient gleichzeitig als Eingang (der aktuelle Wert vor der Ausführung) und als Ausgang (der neue Wert nach der Ausführung). Bei `REQ` wird `OUT := IN` gesetzt, so dass der vorherige Wert überschrieben wird.

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

1. Ein ankommendes Ereignis am Eingang `REQ` startet die Verarbeitung.
2. Der im Algorithmus `REQ` hinterlegte Code wird ausgeführt:
   - `OUT := IN;`  
   Der Wert der Eingangsvariablen `IN` wird in die In‑Out‑Variable `OUT` kopiert.
3. Anschließend wird das Ereignis am Ausgang `CNF` gesendet, um die erfolgreiche Ausführung zu signalisieren.

## Technische Besonderheiten

- Der Baustein enthält nur einen einzigen Zustand (`REQ`), in dem die gesamte Verarbeitung stattfindet. Es handelt sich um einen **einfachen Funktionsblock** (SimpleFB) ohne sequentielle Zustandsautomaten.
- Die In‑Out‑Variable `OUT` erlaubt es, den Baustein direkt an eine persistent beschreibbare Variable (z. B. ein globales Datenobjekt oder eine gekoppelte Hardware‑Adresse) anzubinden, ohne dass eine separate Ausgangsvariable notwendig ist.
- Der Algorithmus ist trivial und führt keinerlei Typ‑ oder Bereichsprüfungen durch.

## Zustandsübersicht

Der Funktionsblock besitzt genau einen Zustand:

| Zustand | Aktion               | Ausgabeereignis | Beschreibung                                   |
|---------|----------------------|-----------------|------------------------------------------------|
| `REQ`   | `OUT := IN`          | `CNF`           | Kopiert den Eingangswert in die In‑Out‑Variable und bestätigt |

Ein Startzustand ist nicht explizit definiert; der Baustein erwartet einen externen Ereignisimpuls auf `REQ`.

## Anwendungsszenarien

- **Parametrierung von Zeichenketten in Steuerungen**: Setzen eines String‑Werts in einer globalen Variable, z. B. eines Gerätenamens oder einer IP‑Adresse.
- **Initialisierung von Textbausteinen**: Überschreiben einer standardmäßigen Zeichenkette in einem übergeordneten FB‑Netzwerk.
- **Test‑ und Debugging‑Umgebungen**: Gezieltes Vorgeben von Werten für nachfolgende Verarbeitungsschritte.

## Vergleich mit ähnlichen Bausteinen

- **SET_BOOL, SET_INT, SET_REAL**: Gleichartig aufgebaute Funktionsblöcke für andere Datentypen. `SET_STRING` unterscheidet sich nur durch den Datentyp `STRING`.
- **MOVE**: Ein generischer Baustein, der Werte unterschiedlicher Datentypen kopieren kann. `SET_STRING` ist dagegen strikt auf `STRING` spezialisiert und arbeitet mit einer In‑Out‑Variable, während `MOVE` separate Eingänge und Ausgänge verwendet.
- **WRITE_STRING**: In einigen Bibliotheken vorhandene Blöcke mit ähnlicher Funktion, jedoch oft mit zusätzlichen Steuer- oder Fehlerausgängen ausgestattet.

## Fazit

Der `SET_STRING`‑Funktionsblock ist ein einfaches, aber effektives Werkzeug zum gezielten Setzen eines String‑Werts in eine In‑Out‑Variable. Er eignet sich besonders für Anwendungen, in denen ein Wert direkt in eine bestehende Variable geschrieben werden muss, ohne dass eine Rücklese‑ oder Vergleichslogik erforderlich ist. Aufgrund seiner minimalen Schnittstelle und der klaren Semantik kann er leicht in komplexere Automatisierungslösungen integriert werden.