# GET_BYTE


![GET_BYTE](./GET_BYTE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **GET_BYTE** dient dem Auslesen einer `BYTE`-Variablen, die über einen **InOut**-Parameter bereitgestellt wird. Der gelesene Wert wird am Ausgang `OUT` gepuffert und steht nach der Ausführung zur Verfügung. Der Baustein wird typischerweise eingesetzt, um einen aktuellen `BYTE`-Wert aus einer externen Quelle (z. B. einem gemeinsamen Datenbereich) abzugreifen, ohne die Quelle selbst zu verändern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                     | Mit Variablen |
|------|-------|-------------------------------|---------------|
| REQ  | Event | Normaler Ausführungsanstoß     | IN            |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                    | Mit Variablen       |
|------|-------|------------------------------|---------------------|
| CNF  | Event | Bestätigung der Ausführung   | OUT, IN            |

### **Daten-Eingänge**

Der Baustein besitzt keine klassischen Dateneingänge, sondern nutzt einen **InOut-Parameter**, der gleichzeitig als Ein- und Ausgang genutzt werden kann:

| Name | Typ    | Initialwert | Kommentar                          |
|------|--------|-------------|------------------------------------|
| IN   | BYTE   | 0           | Quellvariable (lesend über InOut)  |

### **Daten-Ausgänge**

| Name | Typ    | Initialwert | Kommentar                              |
|------|--------|-------------|----------------------------------------|
| OUT  | BYTE   | 0           | Gepufferter Ausgabewert                 |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Baustein wird über ein Ereignis am Eingang `REQ` aktiviert. Daraufhin wird der aktuelle Wert der am **InOut**-Parameter `IN` anliegenden Variable gelesen und in den Ausgang `OUT` kopiert. Anschließend wird das Ereignis `CNF` ausgelöst, das die erfolgreiche Ausführung quittiert. Der Algorithmus ist denkbar einfach:

```
OUT := IN;
```

Da `IN` als InOut-Parameter deklariert ist, muss die aufrufende Applikation eine BYTE-Variable bereitstellen, die sowohl gelesen als auch (bei anderen Bausteinen) geschrieben werden kann. `GET_BYTE` führt jedoch nur eine Leseoperation aus.

## Technische Besonderheiten

- **InOut-Parameter**: Der Baustein greift direkt auf eine externe Variable zu, ohne sie über einen separaten Daten-Eingang zu verbinden. Dies ermöglicht eine effiziente, direkte Datenbindung und spart Ressourcen in der Vernetzung.
- **Gepufferter Ausgang**: Der gelesene Wert wird in `OUT` zwischengespeichert und bleibt bis zur nächsten Ausführung erhalten – auch wenn sich die Quellvariable zwischenzeitlich ändert.
- **Keine Zustandsmaschine**: Der Baustein besteht aus einem einzigen Zustand, was die Implementierung schlank und deterministisch macht.

## Zustandsübersicht

Der Baustein verfügt über genau einen internen Zustand:

| Zustand | Beschreibung                                             | Ausgangsereignis |
|---------|----------------------------------------------------------|------------------|
| REQ     | Kein Warten; sofortiger Ablauf der Leseoperation         | CNF              |

Es gibt keine Wartezustände oder Verzweigungen.

## Anwendungsszenarien

- **Auslesen von Konfigurationswerten**: Ein `BYTE`-Wert aus einem zentralen Datenblock (z. B. einer globalen Konfiguration) wird in einen lokalen Puffer übernommen.
- **Synchronisation zwischen Bausteinen**: Ein anderer Baustein schreibt einen `BYTE` in eine gemeinsame InOut-Variable, und `GET_BYTE` liest diesen Wert bei Bedarf aus.
- **Sichere Datenübernahme**: Durch den gepufferten Ausgang wird verhindert, dass nachfolgende Logik auf einen sich ändernden Quellwert reagiert – sie arbeitet stets mit dem zum Zeitpunkt der Anfrage gültigen Wert.

## Vergleich mit ähnlichen Bausteinen

| Baustein   | Beschreibung                                           | Unterschied zu GET_BYTE                                      |
|------------|--------------------------------------------------------|--------------------------------------------------------------|
| GET_VALUE  | Liest einen Wert aus einem InOut-Parameter aus (typ‑unspezifisch) | GET_BYTE ist auf den Datentyp `BYTE` spezialisiert und daher typsicherer. |
| MOVE       | Kopiert einen Wert von einem Eingang zu einem Ausgang  | MOVE benötigt separate Eingänge und gibt keinen Puffer – GET_BYTE nutzt InOut. |
| READ_BYTE  | Liest ein Byte über eine Hardware-Adresse              | GET_BYTE arbeitet auf der Variablenebene, nicht auf Hardware-Adressen. |

## Fazit

**GET_BYTE** ist ein einfacher, aber nützlicher Baustein, um einen `BYTE`-Wert aus einer externen Quelle über einen InOut-Parameter auszulesen und gepuffert bereitzustellen. Dank des schlanken Designs (ein Zustand, minimale Schnittstelle) eignet er sich besonders für ressourcenkritische Anwendungen und für die Integration in bestehende Kommunikations‑ oder Speicherkonzepte, bei denen der direkte Zugriff auf eine gemeinsam genutzte Variable erwünscht ist.