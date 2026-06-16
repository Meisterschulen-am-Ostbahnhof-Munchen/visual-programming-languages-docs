# GET_UDINT


![GET_UDINT](./GET_UDINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_UDINT** dient dazu, den aktuellen Wert einer als InOut deklarierten Variable vom Typ **UDINT** zu lesen und als gepufferten Ausgang bereitzustellen. Die Pufferung stellt sicher, dass der Ausgangswert während eines Zyklus stabil bleibt, auch wenn die Quelldaten sich später ändern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Normaler Ausführungsanforderung |

*Assoziierte Daten:*
- **IN** (InOut-Variable) wird bei REQ gelesen.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der Ausführung |

*Assoziierte Daten:*
- **OUT** (Ausgangswert) wird nach erfolgreichem Lesen bereitgestellt.
- **IN** (InOut-Variable) wird ebenfalls assoziiert, d. h. ihr Wert kann nach dem Event am Ausgang gelesen werden.

### **Daten-Eingänge**

| Name | Typ | Vorgabewert | Kommentar |
|------|-----|-------------|-----------|
| IN | UDINT (InOut) | 0 | Quellvariable, die gelesen wird |

### **Daten-Ausgänge**

| Name | Typ | Vorgabewert | Kommentar |
|------|-----|-------------|-----------|
| OUT | UDINT | 0 | Gepufferter Ausgangswert |

### **Adapter**
Keine.

## Funktionsweise
Bei einem Ereignis am **REQ**-Eingang führt der Baustein den Algorithmus aus und sendet ein Bestätigungsereignis auf **CNF**. Der Algorithmus kopiert den aktuellen Wert der InOut-Variablen **IN** in die Ausgangsvariable **OUT**. Dadurch wird der Wert zum Zeitpunkt der Anforderung eingefroren und steht bis zur nächsten Anforderung stabil am Ausgang zur Verfügung.

## Technische Besonderheiten
- **InOut‑Variable:** Der Parameter **IN** ist als InOut deklariert. Dies ermöglicht einen direkten Zugriff auf die Speicheradresse der Quellvariablen, was bei der Kommunikation über verteilte Systeme (z. B. Feldbusse) nützlich sein kann. Der FB liest jedoch nur den Wert, er schreibt nicht zurück.
- **Pufferung:** Der Ausgang **OUT** wird nur bei einem **REQ**-Ereignis aktualisiert. Änderungen an **IN** zwischen zwei Anforderungen haben keinen Einfluss auf **OUT**.
- **Keine Seiteneffekte:** Der Baustein verändert die InOut-Variable nicht.

## Zustandsübersicht
Der FB besitzt einen einzigen Zustand:
- **REQ:** Der Algorithmus wird ausgeführt. Nach Kopieren des Wertes wird sofort der Ausgang **CNF** gesetzt.

Es gibt keine weiteren Zustände, d. h. der FB ist immer bereit, eine Anforderung zu bearbeiten.

## Anwendungsszenarien
- **Pufferung von Prozesswerten:** In Automatisierungssystemen, in denen ein Messwert oder eine Stellgröße (z. B. ein Zählerstand oder eine Geschwindigkeit) in einem bestimmten Takt eingefroren werden muss, bevor er an andere Bausteine weitergegeben wird.
- **Entkopplung von Zyklen:** Wenn eine InOut‑Variable von mehreren Bausteinen gelesen wird und ein stabiler Wert innerhalb eines Zyklus benötigt wird.
- **Ersatz für direkten Durchgriff:** Statt einer InOut‑Variable direkt auszulesen, bietet der FB eine klare Schnittstelle (Event‑Eingang, Ausgang) und verbessert die Lesbarkeit des Systems.

## Vergleich mit ähnlichen Bausteinen
- **MUX (Multiplexer):** Ein MUX wählt zwischen mehreren Eingängen aus, während **GET_UDINT** genau einen definierten Wert von einer InOut‑Variablen puffert.
- **GET_DINT / GET_REAL:** Analoge Bausteine für andere Datentypen, die das gleiche Prinzip der gepufferten Ausgabe von InOut‑Werten umsetzen.
- **Latch‑Bausteine:** Diese speichern Werte und geben sie bei einem Ereignis aus; **GET_UDINT** hingegen überschreibt den Ausgang bei jeder Anforderung mit dem aktuellen Wert der Quelle.

## Fazit
Der Funktionsblock **GET_UDINT** ist ein einfaches, aber nützliches Hilfsmittel, um den Wert einer InOut‑Variable vom Typ UDINT stabil und ereignisgesteuert zwischenzuspeichern. Er eignet sich besonders für Anwendungen, in denen ein Zugriff auf externe oder geteilte Variablen in kontrollierten Schritten erfolgen soll, und trägt so zu einer sauberen und vorhersagbaren Signalverarbeitung bei.