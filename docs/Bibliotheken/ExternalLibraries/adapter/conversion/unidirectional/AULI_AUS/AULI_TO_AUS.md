# AULI_TO_AUS


![AULI_TO_AUS](./AULI_TO_AUS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_AUS** ist ein Composite-Baustein, der eine Konvertierung von einem **AULI-Adapter** (ulint, 64‑Bit unsigned) zu einem **AUS-Adapter** (usint, 8‑Bit unsigned) vornimmt. Er kapselt die IEC‑61131‑Funktion **F_ULINT_TO_USINT** in einer adapterbasierten Umgebung, sodass Daten über standardisierte Adapter ausgetauscht werden können.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis- oder Daten-Ein-/Ausgänge auf FB-Ebene. Die gesamte Kommunikation erfolgt über die beiden Adapter.

### **Ereignis-Eingänge**
- über **Socket AULI_IN** (Typ AULI): Ereignis **E1** – initiiert die Datenübergabe und Konvertierung.

### **Ereignis-Ausgänge**
- über **Plug AUS_OUT** (Typ AUS): Ereignis **E1** – wird ausgelöst, sobald der konvertierte Wert am Ausgang anliegt.

### **Daten-Eingänge**
- über **Socket AULI_IN** (Typ AULI): Daten-Eingang **D1** (ULINT) – der zu konvertierende 64‑Bit‑Wert.

### **Daten-Ausgänge**
- über **Plug AUS_OUT** (Typ AUS): Daten-Ausgang **D1** (USINT) – der konvertierte 8‑Bit‑Wert.

### **Adapter**

| Bezeichnung | Typ        | Richtung | Beschreibung                     |
|-------------|------------|----------|----------------------------------|
| AULI_IN     | AULI       | Socket   | Eingangsadapter für ULINT-Daten  |
| AUS_OUT     | AUS        | Plug     | Ausgangsadapter für USINT-Daten  |

## Funktionsweise
1. Über den Socket **AULI_IN** empfängt der FB ein Ereignis an **E1**. Gleichzeitig wird der zugehörige ULINT-Wert an **D1** bereitgestellt.
2. Dieses Ereignis wird an den internen Baustein **F_ULINT_TO_USINT** (Name: `Convert`) weitergeleitet (über die Ereignisverbindung `REQ`).
3. Der ULINT-Wert wird an den Dateneingang **IN** des Konverters übergeben.
4. Nach Abschluss der Konvertierung erzeugt der Konverter das Ereignis **CNF**.
5. Dieses Ereignis wird zum Plug **AUS_OUT** auf dessen Ereigniseingang **E1** übertragen, während der konvertierte USINT-Wert vom Ausgang **OUT** des Konverters an den Datenausgang **D1** des Plugs gelegt wird.
6. Der angeschlossene Empfänger kann nun das Ereignis und den USINT-Wert verarbeiten.

## Technische Besonderheiten
- **Composite-Baustein** – Er enthält eine interne Instanz von **F_ULINT_TO_USINT** aus der IEC‑61131‑Bibliothek.
- **Adapterbasierte Kommunikation** – Keine direkten Daten/Events auf der obersten FB‑Ebene; die Ein‑/Ausgabe erfolgt ausschließlich über die mitgelieferten Adapter (AULI / AUS).
- **Datenverlust möglich** – Da der USINT‑Datentyp nur 8 Bit umfasst, gehen Werte > 255 verloren (abgeschnitten oder wrap‑around, je nach Implementierung des Konverters).
- **Keine eigene Zustandsmaschine** – Der FB ist ein reines Netzwerk aus bestehenden Bausteinen und besitzt keinen eigenen Zustandsautomaten.

## Zustandsübersicht
Aufgrund der Composite‑Natur und des Fehlens einer eigenen Zustandsmaschine entfällt eine Zustandsübersicht. Das Verhalten wird vollständig durch den inneren FB **F_ULINT_TO_USINT** bestimmt.

## Anwendungsszenarien
- **Integration von ULINT‑Datenquellen** (z. B. hochauflösende Zähler, Zeitstempel oder große Sensordaten) in ein Automatisierungssystem, das aufgrund von Speicher- oder Protokollbeschränkungen nur USINT‑Werte verarbeiten kann.
- **Adapter-Konvertierung** in einer verteilten Anwendung, um zwischen zwei unterschiedlichen Adapter-Typen (AULI ↔ AUS) zu vermitteln, ohne die darüber liegende Logik zu ändern.
- **Prototypische Umstellungen** von 64‑Bit auf 8‑Bit Datenpfade während der Entwicklung.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Bausteine wie **AULI_TO_AINT** (ULINT → AINT) oder **AULI_TO_AWORD** (ULINT → AWORD) realisieren analoge Konvertierungen für andere Ausgabetypen. Der vorliegende Baustein spezialisiert sich auf **USINT** – eine besonders speicherschonende Zielgröße. Im Gegensatz zu einer direkten Datenkonvertierung auf Applikationsebene bietet der adapterbasierte Ansatz eine strukturierte, wiederverwendbare Schnittstellenkapselung, die den Austausch von Datenströmen in standardisierten Industrieprotokollen erleichtert.

## Fazit
**AULI_TO_AUS** ist ein praktischer Composite‑Baustein, der eine IEC‑61131‑Konvertierungsfunktion in eine adapterbasierte Umgebung einbettet. Er ermöglicht die transparente Umwandlung von ULINT- zu USINT‑Werten über die entsprechenden Adapter und eignet sich insbesondere für Szenarien, in denen hohe Genauigkeit oder große Wertebereiche auf ein kleineres Datenformat reduziert werden müssen. Der Baustein ist einfach einsetzbar, erfordert aber Aufmerksamkeit bei möglichen Datenverlusten.