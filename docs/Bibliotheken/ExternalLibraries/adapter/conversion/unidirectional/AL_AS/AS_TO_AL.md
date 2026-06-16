# AS_TO_AL


![AS_TO_AL](./AS_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AS_TO_AL** ist ein Composite-Baustein, der einen SINT-Adapter (AS) in einen LWORD-Adapter (AL) umwandelt. Er dient als Brücke zwischen unterschiedlichen Adaptertypen in einer unidirektionalen Kommunikationsstrecke. Der Baustein kapselt die Konvertierungslogik und macht sie für den Anwender als zusammengesetzte Einheit nutzbar.

## Schnittstellenstruktur
Der Baustein besitzt **keine direkten Ereignis- oder Datenschnittstellen** auf oberster Ebene. Die gesamte Ein- und Ausgabe erfolgt über Adapter.

### **Ereignis-Eingänge**
- Keine (Ereignisse werden über den Socket-Adapter AS_IN hereingereicht)

### **Ereignis-Ausgänge**
- Keine (Ereignisse werden über den Plug-Adapter AL_OUT ausgegeben)

### **Daten-Eingänge**
- Keine (Daten werden über den Socket-Adapter AS_IN bereitgestellt)

### **Daten-Ausgänge**
- Keine (Daten werden über den Plug-Adapter AL_OUT bereitgestellt)

### **Adapter**

| Name   | Typ                                    | Richtung | Beschreibung                     |
|--------|----------------------------------------|----------|----------------------------------|
| AS_IN  | adapter::types::unidirectional::AS     | Socket   | SINT-Adapter (Eingang)           |
| AL_OUT | adapter::types::unidirectional::AL     | Plug     | LWORD-Adapter (Ausgang)          |

## Funktionsweise
Der Baustein arbeitet intern mit dem IEC-61131-Konvertierungsbaustein **F_SINT_TO_LWORD**. Sobald ein Ereignis am Ereignisausgang **E1** des Socket-Adapters **AS_IN** eintrifft, wird dieses an den Eingang **REQ** des Konvertierungsbausteins weitergeleitet. Dieser wandelt den SINT-Datenwert von **AS_IN.D1** in einen LWORD-Wert um und gibt ihn an **AL_OUT.D1** aus. Nach erfolgreicher Umwandlung wird ein Bestätigungsereignis an den Ereigniseingang **E1** des Plug-Adapters **AL_OUT** gesendet.

## Technische Besonderheiten
- **Standardkonformität**: Entspricht IEC 61499-2.
- **Urheberrechte**: Der Baustein unterliegt der Eclipse Public License 2.0 (Copyright 2026 HR Agrartechnik GmbH).
- **Version**: 1.0, erstellt von Franz Höpfinger am 17.02.2026.
- **Paketstruktur**: Im Paket `adapter::conversion::unidirectional` organisiert.
- **Abhängigkeiten**: Nutzt den Baustein `iec61131::conversion::F_SINT_TO_LWORD`.

## Zustandsübersicht
Da es sich um einen Composite-Baustein handelt, besitzt er keinen eigenen Zustandsautomaten. Die Zustandslogik wird durch den integrierten Baustein **F_SINT_TO_LWORD** abgebildet, der intern eine einfache Umwandlung ohne Verzögerung oder Fehlerzustände vornimmt. Die Ausführung erfolgt streng ereignisgesteuert.

## Anwendungsszenarien
- **Adapterkonvertierung**: Verbindung von Komponenten, die einen SINT-Adapter bereitstellen, mit Komponenten, die einen LWORD-Adapter erwarten.
- **Datenanpassung**: Einsatz in heterogenen Automatisierungssystemen, in denen unterschiedliche Datentypen auf Adapterebene harmonisiert werden müssen.
- **Modulare Wiederverwendung**: Der Baustein kann in Bibliotheken für unidirektionale Konvertierungen eingebunden werden.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Adapter-Konvertierungsbausteine existieren für andere Datentypen (z. B. BOOL, INT, DWORD). Der **AS_TO_AL** ist speziell auf die Umwandlung von **SINT** (Signed Short Integer, 8 Bit) nach **LWORD** (Long Word, 64 Bit) ausgelegt. Im Gegensatz zu generischen Funktionsbausteinen wird die Konvertierung hier bereits auf Adapterebene bereitgestellt, was eine einfachere Verdrahtung im Netzwerk ermöglicht.

## Fazit
Der Composite-Baustein **AS_TO_AL** bietet eine kompakte und standardkonforme Lösung zur Umwandlung eines SINT-Adapters in einen LWORD-Adapters. Durch die Kapselung der Konvertierungslogik wird die Übersichtlichkeit des Anwendungsnetzwerks erhöht und die Wiederverwendbarkeit gefördert. Der Baustein eignet sich besonders für modulare Automatisierungsprojekte, bei denen unterschiedliche Datentypen auf Adapterebene zusammengeführt werden müssen.