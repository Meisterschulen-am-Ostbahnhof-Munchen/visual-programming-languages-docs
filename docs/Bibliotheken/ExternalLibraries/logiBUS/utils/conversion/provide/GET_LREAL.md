# GET_LREAL


![GET_LREAL](./GET_LREAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `GET_LREAL` dient dem lesenden Zugriff auf eine `LREAL`-Variable (64‑Bit‑Gleitkommazahl), die als InOut‑Parameter übergeben wird. Der gelesene Wert wird intern gepuffert und am Ausgang `OUT` zur Verfügung gestellt. Die Ausführung wird über ein Ereignis gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Normaler Ausführungsanstoß; liest den Wert von `IN` |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung der Ausführung; wird nach dem Lesen gesendet |

### **Daten-Eingänge**
Der Baustein besitzt keine eigenständigen Dateneingänge. Die Quelldaten werden über den InOut‑Parameter `IN` bereitgestellt.

### **Daten-Ausgänge**
| Ausgang | Datentyp | Initialwert | Kommentar                  |
|---------|----------|-------------|----------------------------|
| OUT     | LREAL    | 0.0         | Gepufferter Ausgabewert    |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Ein Ereignis am Eingang `REQ` löst die Verarbeitung aus.
2. Der Baustein führt die ST‑Anweisung `OUT := IN;` aus. Dabei wird der aktuelle Wert der InOut‑Variable `IN` gelesen und in der lokalen Ausgangsvariablen `OUT` zwischengespeichert.
3. Nach erfolgreichem Lesen wird das Ereignis `CNF` ausgegeben. Der Wert von `OUT` bleibt bis zur nächsten Ausführung erhalten.

## Technische Besonderheiten
- Die Quelle `IN` ist als **InOut‑Variable** deklariert. Sie muss von der aufrufenden Umgebung mit einer tatsächlichen Variablen (z. B. einer globalen oder einer Hardware‑Ressource) verbunden werden.
- Der Baustein puffert den gelesenen Wert: solange kein neuer `REQ`‑Impuls erfolgt, liefert `OUT` den zuletzt gelesenen Zustand.
- Beide Parameter (`IN` und `OUT`) sind mit dem Initialwert `0.0` belegt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsbaustein (SimpleFB) handelt, ist nur ein einziger ECC‑Zustand vorhanden:

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ     | `OUT := IN;` | CNF |

## Anwendungsszenarien
- **Gepuffertes Lesen einer hochfrequenten Prozessgröße** (z. B. Temperatur oder Druck), um den Wert im Steuerungszyklus konstant zu halten.
- **Zugriff auf eine shared Memory‑Variable** in einer Multitasking‑Umgebung, bei der die Lesegeschwindigkeit entkoppelt werden soll.
- **Vorbereitung von Daten für nachgelagerte Berechnungen**, die auf einen stabilen, zwischengespeicherten Gleitkommawert angewiesen sind.

## Vergleich mit ähnlichen Bausteinen
Bausteine wie `GET_REAL` oder `GET_INT` arbeiten nach dem gleichen Prinzip, jedoch mit kürzeren Datentypen. `GET_LREAL` ist speziell für Anwendungen ausgelegt, die eine hohe numerische Genauigkeit (64‑Bit) erfordern. Im Unterschied zu reinen Lesebausteinen ohne Pufferung (z. B. direkte Variablenverknüpfung) garantiert der gepufferte Ausgang eine deterministische und vom Zeitpunkt des Lesens unabhängige Bereitstellung.

## Fazit
`GET_LREAL` ist ein einfacher, zuverlässiger Baustein zum gepufferten Auslesen einer `LREAL`‑Quelle. Er eignet sich besonders für die Entkopplung von Lese- und Verarbeitungslogik und stellt sicher, dass der bereitgestellte Wert über einen kompletten Ausführungszyklus konstant bleibt.