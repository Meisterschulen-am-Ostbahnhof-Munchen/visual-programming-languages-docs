# GET_WSTRING


![GET_WSTRING](./GET_WSTRING.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_WSTRING** dient dem Auslesen einer WSTRING-Variablen über einen InOut-Parameter und stellt den gelesenen Wert gepuffert als Datenausgang bereit. Er wird typischerweise eingesetzt, um einen externen WSTRING-Wert in die interne Verarbeitung eines Applikationsbausteins zu übernehmen, ohne den Ursprungswert zu verändern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datentyp | Beschreibung |
|----------|----------|--------------|
| REQ      | Event    | Normale Ausführungsanforderung – löst das Lesen der InOut-Variablen aus. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Beschreibung |
|----------|----------|--------------|
| CNF      | Event    | Bestätigung der Ausführung – wird nach dem erfolgreichen Kopiervorgang gesendet. |

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
|----------|----------|--------------|
| IN       | WSTRING  | InOut-Quellvariable, deren Wert ausgelesen wird. (Die Variable wird nicht verändert.) |

### **Daten-Ausgänge**

| Variable | Datentyp | Beschreibung |
|----------|----------|--------------|
| OUT      | WSTRING  | Gepufferter Ausgabewert – enthält den zum Zeitpunkt des REQ-Ereignisses gelesenen Inhalt von IN. |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein verfügt über einen einzigen Echtzeitschritt (EC State) namens `REQ`. Sobald am Ereigniseingang **REQ** ein Impuls eintrifft, wird der hinterlegte Algorithmus ausgeführt:

1. Der aktuelle Wert der InOut‑Variablen **IN** wird gelesen und direkt der Ausgangsvariablen **OUT** zugewiesen (`OUT := IN`).
2. Anschließend wird das Ereignis **CNF** ausgelöst, um dem aufrufenden Netzwerk die erfolgreiche Übernahme zu signalisieren.

Die InOut‑Variable bleibt unverändert; es findet lediglich ein lesender Zugriff statt.

## Technische Besonderheiten
- **InOut‑Nutzung**: Die Variable `IN` wird formal als `InOut` deklariert. Dies erlaubt dem FB, auf die Speicheradresse der angeschlossenen Quelle zuzugreifen, ohne eine separate Eingangsvariable zu benötigen. Die Variable kann daher sowohl von außen beschrieben als auch innerhalb des FB gelesen werden.
- **Gepufferter Ausgang**: Der Wert von `OUT` bleibt stabil, bis der FB durch ein erneutes **REQ** aktualisiert wird. So kann der nachgeschaltete Teil der Applikation jederzeit auf einen konsistenten Wert zugreifen.
- **Typreinheit**: Der FB arbeitet ausschließlich mit dem Datentyp `WSTRING`. Für andere Datentypen sind eigene Bausteine (z. B. `GET_STRING`, `GET_DINT`) erforderlich.

## Zustandsübersicht
Der FB besitzt nur einen aktiven Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Initial- und Arbeitszustand. Bei jedem **REQ**-Ereignis wird der Algorithmus ausgeführt und **CNF** gesendet. Es gibt keine weiteren Verzweigungen oder Wartezustände. |

## Anwendungsszenarien
- **Datenübernahme von einer externen WSTRING-Quelle** – z. B. Lesen einer globalen Konfigurationszeichenkette oder eines von einem anderen Baustein bereitgestellten WSTRING-Werts.
- **Entkopplung von Lese- und Schreibzugriffen** – Der Wert aus einer gemeinsam genutzten Variable kann sicher gepuffert werden, bevor er in der eigenen Logik weiterverarbeitet wird.
- **Realisierung eines "Get"-Funktionsblocks** in einer InOut-basierten Architektur, wie sie häufig in der **EC‑61499**‑Vernetzung verwendet wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Datentyp | Besonderheit |
|----------|----------|--------------|
| GET_STRING | STRING | Analoger FB für ASCII-Zeichenketten (nicht Unicode). |
| GET_DINT   | DINT   | Für 32‑Bit‑Ganzzahlen. |
| FORCE      | Jeder Typ | Erzwingt einen Wert unabhängig von der Quelle, oft mit zusätzlichem Rücksetzmechanismus. |

**GET_WSTRING** unterscheidet sich von diesen durch die spezifische Unterstützung des breiten Zeichentyps (WSTRING), der für Unicode‑Zeichenfolgen (UTF‑16) verwendet wird. Es handelt sich um einen einfachen, auf Lesen und Puffern beschränkten Baustein ohne Nebenwirkungen.

## Fazit
Der **GET_WSTRING** ist ein schlanker, leicht verständlicher Funktionsblock, der in IEC‑61499‑Umgebungen eine grundlegende Aufgabe übernimmt: das sichere Auslesen einer WSTRING-InOut‑Variablen und die Bereitstellung eines gepufferten Ausgangswerts. Seine einfache Struktur und der Verzicht auf Zustandsverzweigungen machen ihn ideal für den Einsatz in datenorientierten Steuerungsaufgaben, bei denen die Werte einer externen Quelle einmalig oder zyklisch übernommen werden müssen.