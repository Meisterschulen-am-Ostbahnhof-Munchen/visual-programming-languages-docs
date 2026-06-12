# AUDI_SPLIT_7


![AUDI_SPLIT_7](./AUDI_SPLIT_7.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_SPLIT_7` dient dazu, ein einzelnes AUDI-Eingangssignal auf sieben identische AUDI-Ausgangssignale zu verteilen. Er ist als generischer Baustein konzipiert und eignet sich für alle unidirektionalen AUDI-Adaptertypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**

| Name   | Typ                            | Richtung |
|--------|--------------------------------|----------|
| `IN`   | `adapter::types::unidirectional::AUDI` | Socket (Eingang) |
| `OUT1` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT2` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT3` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT4` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT5` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT6` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |
| `OUT7` | `adapter::types::unidirectional::AUDI` | Plug (Ausgang)   |

Alle Adapter sind vom unidirektionalen Typ `AUDI` und übertragen Datenfluss ausschließlich vom Socket zu den Plugs.

## Funktionsweise

Der Baustein kopiert die über den Socket `IN` eingehenden AUDI-Daten unverändert auf alle sieben Plug-Ausgänge `OUT1` bis `OUT7`. Es erfolgt keine Verarbeitung oder Umwandlung der Daten – die Funktion beschränkt sich auf eine reine 1-zu-7-Verteilung (Fan-Out). Da keine Ereignisse oder explizite Datenports vorhanden sind, wird das Signalverhalten vollständig durch die angeschlossenen Adapter definiert.

## Technische Besonderheiten

- **Generischer Typ**: Über das Attribut `eclipse4diac::core::GenericClassName` (`'GEN_AUDI_SPLIT'`) wird der Baustein als generisch gekennzeichnet. Damit kann er für verschiedene konkrete Ausprägungen des AUDI-Adapters verwendet werden, ohne dass eine separate Implementierung erforderlich ist.
- **Keine Laufzeitabhängigkeit**: Der Baustein besitzt keinen Algorithmus und kein Zustandsdiagramm; die Signalweitergabe erfolgt rein strukturell durch die Adapterverkabelung.
- **Typ-Hash**: Das Attribut `eclipse4diac::core::TypeHash` ist leer, was bedeutet, dass die Typidentität zur Laufzeit nicht zusätzlich abgesichert wird.

## Zustandsübersicht

Der Baustein enthält keine Zustandsmaschine (ECC). Das Verhalten ist vollständig deterministisch und ereignislos – eine Zustandsdarstellung ist daher nicht erforderlich.

## Anwendungsszenarien

- **Signalverteilung**: Ein von einer Sensor- oder Steuereinheit kommendes AUDI-Signal muss parallel an mehrere Verbraucher (Aktoren, Anzeigen, Überwachungssysteme) weitergeleitet werden.
- **Systemerweiterung**: Vorhandene Systeme, die ein einzelnes AUDI-Signal bereitstellen, sollen um weitere Komponenten ergänzt werden, ohne die Quelllogik zu ändern.
- **Testaufbauten**: Ein generiertes Testsignal soll zeitgleich an mehrere Prüflinge gesendet werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein         | Verteilung               | Adaptertyp             |
|------------------|--------------------------|------------------------|
| `AUDI_SPLIT_7`   | 1 Eingang → 7 Ausgänge   | Unidirektional `AUDI` |
| `SPLIT_1_TO_2`  (analog) | 1 → 2       | Beliebig (generisch)   |
| `AUDI_MERGE`     | Mehrere Eingänge → 1      | Unidirektional `AUDI` |

Während `AUDI_SPLIT_7` auf den spezifischen AUDI-Adaptertyp ausgelegt ist, existieren generische Split-Bausteine für andere Datenformate. Die Beschränkung auf eine feste Anzahl von sieben Ausgängen unterscheidet ihn von flexiblen Splittern mit parametrierbarer Ausgangsanzahl.

## Fazit

`AUDI_SPLIT_7` ist ein einfacher, aber effektiver Baustein zum Verteilen eines AUDI-Signals auf sieben identische Pfade. Durch die generische Auslegung kann er in verschiedenen Kontexten wiederverwendet werden. Der Verzicht auf Ereignisse und interne Logik macht ihn leichtgewichtig und zuverlässig für reine Signalverteilungsaufgaben.