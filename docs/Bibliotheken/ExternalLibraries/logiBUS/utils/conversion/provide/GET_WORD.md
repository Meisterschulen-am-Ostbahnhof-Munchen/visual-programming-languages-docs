# GET_WORD


![GET_WORD](./GET_WORD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **GET_WORD** dient dem Auslesen eines WORD-Werts aus einer InOut-Variablen und stellt diesen als gepufferten Ausgang zur Verfügung. Er wird typischerweise eingesetzt, um einen aktuellen Wert von einer Hardware-peripherie oder einer gemeinsam genutzten Speicherstelle zu erfassen und für die weitere Verarbeitung im Steuerungsprogramm bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Normale Ausführungsanforderung; löscht den Lesevorgang aus und gibt das Ergebnis am Ausgang `OUT` aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der Ausführung; signalisiert, dass der Wert von `IN` erfolgreich in `OUT` übernommen wurde. |

### **Daten-Eingänge**

Der FB besitzt keine expliziten Dateneingänge im klassischen Sinne, sondern nutzt eine **InOut-Variable**:

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| IN       | WORD  | Quellvariable (InOut), aus der der gelesene Wert stammt. Der FB greift lesend darauf zu. |

### **Daten-Ausgänge**

| Ausgang | Typ   | Beschreibung                                   |
|---------|-------|------------------------------------------------|
| OUT     | WORD  | Gepufferter Ausgangswert – Kopie von `IN` zum Zeitpunkt der letzten `REQ`-Ausführung. |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

1. Der FB startet mit einem **REQ**-Ereignis am Eingang.
2. Der Algorithmus **REQ** wird ausgeführt:
   - Der aktuelle Wert der InOut-Variablen `IN` wird in den Ausgang `OUT` kopiert.
3. Nach erfolgreicher Zuweisung wird das **CNF**-Ereignis am Ausgang gesendet.

Somit liegt der einmal gelesene Wert solange am Ausgang `OUT` an, bis ein erneuter **REQ**-Impuls eine Aktualisierung auslöst. Dies entspricht einer gepufferten Leseoperation.

## Technische Besonderheiten

- **InOut-Verwendung** – Der Baustein greift lesend auf eine InOut-Variable zu, die typischerweise mit einem Speicher- oder Hardware-Register verbunden ist.
- **Pufferung** – Der gelesene Wert wird im Ausgang `OUT` gehalten, selbst wenn sich die Quelle `IN` später ändert. Erst ein erneuter **REQ**-Aufruf aktualisiert den Puffer.
- **Initialisierung** – `IN` und `OUT` sind standardmäßig mit 0 vorbelegt.

## Zustandsübersicht

Der FB implementiert einen einfachen Zustandsautomaten mit nur einem Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Immer aktiv bei Eintreffen von **REQ**; führt die Zuweisung `OUT := IN` durch und sendet **CNF**. |

Es gibt keine weiteren Zustände wie IDLE oder WARTE, da die Logik streng ereignisgesteuert ohne Verzweigung ist.

## Anwendungsszenarien

- **Einlesen eines Hardware-Registers** – Z. B. Auslesen eines Analog-Digital-Wandlerwerts oder eines Zählerstands, der als WORD vorliegt.
- **Sichern eines flüchtigen Werts** – Wenn die Quelle nur kurzzeitig stabil ist (z. B. nach einem Interrupt), kann der FB den Wert in einem definierten Moment einfrieren.
- **Zugriff auf gemeinsam genutzte Variablen** – In Mehrfachaufruf-Umgebungen wird der aktuelle Stand einer globalen WORD-Variablen abgeholt und lokal weiterverarbeitet.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|-------------|
| **MOVE** | Kopiert einen Wert von einem Dateneingang zu einem Ausgang. `GET_WORD` liest dagegen aus einer InOut-Variablen, die oft eine Verbindung zu einer externen Ressource darstellt. |
| **READ** | Oft standardisiert für IEC 61499, liest aus einem Prozessabbild. `GET_WORD` ist spezifischer für eine gepufferte WORD-Übernahme aus einer InOut-Stelle. |
| **LATCH** | Hält einen Wert nach einem Setz-Impuls. `GET_WORD` aktualisiert nur bei jedem **REQ**, ähnelt also einem getakteten Latch, ist aber nicht setz-/rücksetzbar. |

## Fazit

**GET_WORD** ist ein einfacher, aber nützlicher Funktionsblock für das gezielte Auslesen und Puffern eines WORD-Werts aus einer InOut-Variablen. Er eignet sich besonders für Anwendungen, in denen zu einem bestimmten Ereigniszeitpunkt der aktuelle Stand einer Quelle festgehalten und anschließend stabil zur Verfügung gestellt werden muss. Der FB ist leicht verständlich, ressourcenschonend und lässt sich nahtlos in ereignisgesteuerte Abläufe integrieren.